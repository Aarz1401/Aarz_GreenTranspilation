#!/usr/bin/env python3
"""Translate mirrored Kamyu Python 2 solutions to modern C++ using OpenAI models.

This utility walks a mirror folder created by ``crossref_from_csv.py`` (the
``kamyu_hard_mirror`` layout) and, for every Python 2 solution it finds, asks a
language model (GPT-5 or compatible) to emit an equivalent C++ translation. The
outputs are stored alongside manifests so subsequent verification runs and
resumptions remain deterministic.

Typical usage::

    python translate_py2_to_cpp.py \
        --root kamyu_hard_mirror \
        --out-subdir cpp_gpt \
        --model gpt-5.0-mini \
        --limit 5

Environment:
    * ``OPENAI_API_KEY`` must be present (``python-dotenv`` is loaded by
      default so a ``.env`` file in the project root is sufficient).

The script is intentionally single-threaded. Rate limits are handled by
``tenacity`` retries, and a ``--sleep`` option provides additional spacing
between requests if desired.
"""
from __future__ import annotations

import argparse
import datetime as dt
import json
import os
import sys
import time
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, List, Optional

from dotenv import load_dotenv  # type: ignore
from openai import OpenAI  # type: ignore
from tenacity import (  # type: ignore
    retry,
    retry_if_exception_type,
    stop_after_attempt,
    wait_random_exponential,
)

# ---------------------------------------------------------------------------
# Prompts
# ---------------------------------------------------------------------------
SYSTEM_PROMPT = (
    "You are an elite competitive-programming mentor who fluently translates "
    "LeetCode-style Python 2 solutions into efficient, clean modern C++ (C++17). "
    "Preserve algorithmic intent, helper functions, and comments. Use standard "
    "library facilities that compile on LeetCode. Keep class/function signatures "
    "matching the original problem expectations. Return only runnable C++ source "
    "code—no explanations or tests."
)

USER_TEMPLATE = """Problem slug: {slug}
Python source file: {source_name}

Translate the following Python 2 code into a single C++17 source file suitable
for submitting to LeetCode. Maintain the public class/method signatures expected
by LeetCode. Use only the C++ standard library allowed on LeetCode. Prefer
explicit types, std::vector, std::array, etc.

```python
{python_code}
```
"""


@dataclass
class ProblemContext:
    slug: str
    py_file: Path
    out_file: Path
    manifest: Optional[dict]


class TranslationError(RuntimeError):
    """Raised when the model fails to yield usable C++ code."""


# ---------------------------------------------------------------------------
# Utility helpers
# ---------------------------------------------------------------------------
def load_manifest(problem_dir: Path) -> Optional[dict]:
    manifest_path = problem_dir / "manifest.json"
    if manifest_path.exists():
        try:
            return json.loads(manifest_path.read_text(encoding="utf-8"))
        except Exception:
            return None
    return None


def infer_slug(problem_dir: Path, manifest: Optional[dict]) -> str:
    if manifest:
        slug = manifest.get("title_slug") or manifest.get("slug")
        if slug:
            return str(slug)
    name = problem_dir.name
    if "__" in name:
        return name.split("__", 1)[1]
    return name


def find_python_files(problem_dir: Path) -> List[Path]:
    py_dir = problem_dir / "python"
    if not py_dir.exists():
        return []
    return sorted([p for p in py_dir.iterdir() if p.is_file() and p.suffix == ".py"])


def ensure_out_subdir(problem_dir: Path, out_subdir: str) -> Path:
    folder = problem_dir / out_subdir
    folder.mkdir(parents=True, exist_ok=True)
    return folder


def ensure_client() -> OpenAI:
    load_dotenv()
    if not os.getenv("OPENAI_API_KEY"):
        raise SystemExit(
            "OPENAI_API_KEY is missing. Set it in your environment or a .env file."
        )
    return OpenAI()


# ---------------------------------------------------------------------------
# Model interaction
# ---------------------------------------------------------------------------
@retry(
    reraise=True,
    stop=stop_after_attempt(5),
    wait=wait_random_exponential(multiplier=1, max=60),
    retry=retry_if_exception_type(Exception),
)
def call_model(
    client: OpenAI,
    model: str,
    slug: str,
    source_name: str,
    python_code: str,
    temperature: float,
    max_output_tokens: int,
) -> str:
    response = client.responses.create(
        model=model,
        temperature=temperature,
        max_output_tokens=max_output_tokens,
        input=[
            {
                "role": "system",
                "content": [{"type": "text", "text": SYSTEM_PROMPT}],
            },
            {
                "role": "user",
                "content": [
                    {
                        "type": "text",
                        "text": USER_TEMPLATE.format(
                            slug=slug, source_name=source_name, python_code=python_code
                        ),
                    }
                ],
            },
        ],
    )

    if hasattr(response, "output_text") and response.output_text:
        return response.output_text

    choices = getattr(response, "choices", None)
    if choices:
        return "\n".join(choice.message["content"] for choice in choices if choice)

    raise TranslationError("Model response did not contain any text content.")


def extract_cpp_code(raw_text: str) -> str:
    text = raw_text.strip()
    if "```" not in text:
        return text

    code_blocks: List[str] = []
    lines = text.splitlines()
    inside = False
    fence_lang = None
    buf: List[str] = []
    for line in lines:
        if line.strip().startswith("```"):
            if not inside:
                inside = True
                fence_lang = line.strip().strip("`").strip().lower()
                buf = []
                continue
            else:
                if not fence_lang or "cpp" in fence_lang or "c++" in fence_lang:
                    code_blocks.append("\n".join(buf).strip())
                inside = False
                fence_lang = None
                buf = []
                continue
        if inside:
            buf.append(line)
    if code_blocks:
        return code_blocks[0]
    return text


# ---------------------------------------------------------------------------
# Core workflow
# ---------------------------------------------------------------------------
def iter_problems(
    root: Path, slugs: Optional[set[str]], out_subdir: str
) -> Iterable[ProblemContext]:
    for problem_dir in sorted([p for p in root.iterdir() if p.is_dir()]):
        manifest = load_manifest(problem_dir)
        slug = infer_slug(problem_dir, manifest)
        if slugs and slug not in slugs:
            continue
        py_files = find_python_files(problem_dir)
        if not py_files:
            continue
        out_dir = ensure_out_subdir(problem_dir, out_subdir)
        for py_file in py_files:
            out_file = out_dir / (py_file.stem + ".cpp")
            yield ProblemContext(slug=slug, py_file=py_file, out_file=out_file, manifest=manifest)


def translate_problem(
    client: OpenAI,
    ctx: ProblemContext,
    *,
    overwrite: bool,
    temperature: float,
    max_output_tokens: int,
    model: str,
    sleep: float,
    dry_run: bool,
    meta_dir: Path,
):
    if ctx.out_file.exists() and not overwrite:
        print(f"[skip] {ctx.slug} already translated -> {ctx.out_file.relative_to(meta_dir.parent)}")
        return

    python_code = ctx.py_file.read_text(encoding="utf-8")
    if dry_run:
        print(f"[dry-run] Would translate {ctx.py_file}")
        return

    print(f"[translate] slug={ctx.slug} model={model} source={ctx.py_file.name}")
    raw_text = call_model(
        client=client,
        model=model,
        slug=ctx.slug,
        source_name=ctx.py_file.name,
        python_code=python_code,
        temperature=temperature,
        max_output_tokens=max_output_tokens,
    )
    cpp_code = extract_cpp_code(raw_text)
    if not cpp_code.strip():
        raise TranslationError(f"Empty code returned for {ctx.slug}")

    ctx.out_file.parent.mkdir(parents=True, exist_ok=True)
    ctx.out_file.write_text(cpp_code.rstrip() + "\n", encoding="utf-8")

    metadata = {
        "slug": ctx.slug,
        "source_py": ctx.py_file.as_posix(),
        "generated_cpp": ctx.out_file.as_posix(),
        "model": model,
        "temperature": temperature,
        "max_output_tokens": max_output_tokens,
        "timestamp_utc": dt.datetime.utcnow().isoformat() + "Z",
        "manifest": ctx.manifest or {},
    }
    meta_path = ctx.out_file.with_suffix(ctx.out_file.suffix + ".meta.json")
    meta_path.write_text(json.dumps(metadata, ensure_ascii=False, indent=2), encoding="utf-8")

    with open(meta_dir / "translations_history.jsonl", "a", encoding="utf-8") as history:
        history.write(json.dumps(metadata, ensure_ascii=False) + "\n")

    if sleep > 0:
        time.sleep(sleep)


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------
def parse_args(argv: Optional[List[str]] = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", default="kamyu_hard_mirror", help="Mirror root directory to scan")
    parser.add_argument("--out-subdir", default="cpp_gpt", help="Subfolder name for generated C++ files")
    parser.add_argument("--model", default=os.getenv("OPENAI_MODEL", "gpt-5.0"), help="Model name to request")
    parser.add_argument("--temperature", type=float, default=0.2, help="Sampling temperature")
    parser.add_argument("--max-output-tokens", type=int, default=4096, help="Max tokens for model output")
    parser.add_argument("--sleep", type=float, default=2.0, help="Seconds to sleep after each successful call")
    parser.add_argument("--limit", type=int, default=0, help="Optional limit on number of Python files processed")
    parser.add_argument("--slug", action="append", default=None, help="Restrict to specific slug(s). Can be repeated or comma-separated")
    parser.add_argument("--overwrite", action="store_true", help="Overwrite existing translations")
    parser.add_argument("--dry-run", action="store_true", help="List files without calling the API")
    return parser.parse_args(argv)


def main(argv: Optional[List[str]] = None) -> int:
    args = parse_args(argv)

    root = Path(args.root).resolve()
    if not root.exists():
        raise SystemExit(f"Mirror root not found: {root}")

    slugs: Optional[set[str]] = None
    if args.slug:
        slugs = set()
        for entry in args.slug:
            slugs.update(x.strip() for x in entry.split(",") if x.strip())

    client = ensure_client()

    processed = 0
    meta_dir = root / ".gpt_cache"
    meta_dir.mkdir(parents=True, exist_ok=True)

    try:
        for ctx in iter_problems(root, slugs, args.out_subdir):
            translate_problem(
                client,
                ctx,
                overwrite=args.overwrite,
                temperature=args.temperature,
                max_output_tokens=args.max_output_tokens,
                model=args.model,
                sleep=args.sleep,
                dry_run=args.dry_run,
                meta_dir=meta_dir,
            )
            processed += 1
            if args.limit and processed >= args.limit:
                break
    except TranslationError as exc:
        print(f"[error] {exc}", file=sys.stderr)
        return 2

    print(f"Done. Processed {processed} Python file(s). Output under '{args.out_subdir}'.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
