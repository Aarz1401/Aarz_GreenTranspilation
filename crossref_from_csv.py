
#!/usr/bin/env python3

"""
crossref_from_csv.py
--------------------

Given:
  - a CSV of LeetCode problems you exported from whiskwhite/leetcode-complete
    (e.g., the output of pull_whiskwhite_problems_v2.py)
  - a local clone of kamyu104/LeetCode-Solutions

This script cross-references the problems with Kamyu's Python/C++ solutions,
without hitting leetcode.com. It writes a CSV + SQLite database and can optionally
mirror matched solution files into a structured output folder.

Typical use (your paths):
-------------------------
python crossref_from_csv.py \
  --kamyu-dir "/Users/aadil/Aarz_GreenTranspilation/LeetCode-Solutions" \
  --in-csv whisk_hard_after_may2024.csv \
  --out-csv crossref_hard_kamyu.csv \
  --out-db crossref_hard_kamyu.db \
  --mirror-dir kamyu_hard_mirror

Dependencies:
-------------
pip install pandas python-dateutil tqdm
"""

import argparse
import csv
import datetime as dt
import json
import os
import re
import shutil
import sqlite3
import unicodedata
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import Dict, List, Optional

try:
    import pandas as pd  # type: ignore
except Exception:
    pd = None

try:
    from tqdm import tqdm  # type: ignore
except Exception:
    def tqdm(x, **kwargs):
        return x


LANG_DIRS = {
    "python": ["Python", "Python3"],
    "cpp": ["C++"],
}

EXTS = {
    "python": [".py"],
    "cpp": [".cc", ".cpp", ".cxx", ".C"],
}

STOPWORDS = {"a","an","the","and","of","to","for","with","in","on","by","from"}

@dataclass
class KamyuIndex:
    name_to_paths: Dict[str, List[str]]
    id_to_paths: Dict[str, List[str]]
    all_paths: List[str]


def _norm(s: str) -> str:
    s = unicodedata.normalize("NFKD", s)
    s = s.lower()
    s = re.sub(r"[^a-z0-9]+", "-", s)
    s = re.sub(r"-+", "-", s).strip("-")
    return s


def _norm_underscore(s: str) -> str:
    s = unicodedata.normalize("NFKD", s)
    s = s.lower()
    s = re.sub(r"[^a-z0-9]+", "_", s)
    s = re.sub(r"_+", "_", s).strip("_")
    return s


def _remove_stopwords_norm(title: str) -> str:
    toks = re.split(r"[^a-z0-9]+", _norm(title))
    toks = [t for t in toks if t and t not in STOPWORDS]
    return "-".join(toks)


def _extract_frontend_id_candidates(name: str) -> List[str]:
    digits = re.findall(r"\d{1,5}", name)
    uniq = []
    for d in digits:
        if d not in uniq:
            uniq.append(d)
    uniq.sort(key=lambda x: (-len(x), int(x)))
    return uniq


def index_kamyu(kamyu_dir: Path, lang: str) -> KamyuIndex:
    if lang not in LANG_DIRS:
        raise ValueError(f"Unsupported lang: {lang}")
    name_to_paths = {}
    id_to_paths = {}
    all_paths = []

    for sub in LANG_DIRS[lang]:
        root = kamyu_dir / sub
        if not root.exists():
            continue
        for p in root.rglob("*"):
            if p.is_file() and p.suffix in EXTS[lang]:
                rel = p.relative_to(kamyu_dir).as_posix()
                all_paths.append(rel)
                base = p.stem
                n1 = _norm(base)
                n2 = _norm_underscore(base)
                for n in {n1, n2}:
                    if n:
                        name_to_paths.setdefault(n, []).append(rel)
                for d in _extract_frontend_id_candidates(base):
                    id_to_paths.setdefault(d.lstrip("0") or "0", []).append(rel)

    return KamyuIndex(name_to_paths, id_to_paths, all_paths)


@dataclass
class MatchResult:
    frontend_id: str
    title: str
    title_slug: str
    created_at_approx: str
    difficulty: str
    has_python: bool
    python_path: Optional[str]
    has_cpp: bool
    cpp_path: Optional[str]
    match_strategy: str


def find_match(
    row: dict,
    idx_py: KamyuIndex,
    idx_cpp: KamyuIndex
) -> MatchResult:
    fid = str(row.get("frontend_id") or "").strip()
    title = (row.get("title") or "").strip()
    slug  = (row.get("title_slug") or "").strip()
    created = (row.get("created_at_approx") or "").strip()
    diff = (row.get("difficulty") or "").strip()

    cand = []
    if slug:
        cand += [_norm(slug), _norm_underscore(slug)]
    if title:
        cand += [_norm(title), _norm_underscore(title), _remove_stopwords_norm(title)]
    cand = [c for c in dict.fromkeys(cand) if c]

    def probe_names(cands, idx: KamyuIndex) -> Optional[str]:
        for c in cands:
            if c in idx.name_to_paths:
                paths = sorted(idx.name_to_paths[c], key=lambda x: (len(x), x))
                return paths[0]
        return None

    py_path = probe_names(cand, idx_py) if idx_py else None
    cpp_path = probe_names(cand, idx_cpp) if idx_cpp else None
    strategy = "name:slug/title"

    if (not py_path or not cpp_path) and fid:
        py_id_paths = idx_py.id_to_paths.get(fid) if idx_py else None
        cpp_id_paths = idx_cpp.id_to_paths.get(fid) if idx_cpp else None
        if not py_path and py_id_paths:
            py_path = sorted(py_id_paths, key=lambda x: (len(x), x))[0]
        if not cpp_path and cpp_id_paths:
            cpp_path = sorted(cpp_id_paths, key=lambda x: (len(x), x))[0]
        if (py_id_paths or cpp_id_paths):
            strategy = "id-in-filename"

    def probe_contains(cands, idx: KamyuIndex) -> Optional[str]:
        for c in cands:
            if len(c) < 6:
                continue
            for k in idx.name_to_paths.keys():
                if c in k or k in c:
                    paths = sorted(idx.name_to_paths[k], key=lambda x: (len(x), x))
                    return paths[0]
        return None

    if not py_path and idx_py:
        alt = probe_contains(cand, idx_py)
        if alt:
            py_path = alt
            strategy += "+py~contains"
    if not cpp_path and idx_cpp:
        alt = probe_contains(cand, idx_cpp)
        if alt:
            cpp_path = alt
            strategy += "+cpp~contains"

    return MatchResult(
        frontend_id=fid,
        title=title,
        title_slug=slug,
        created_at_approx=created,
        difficulty=diff,
        has_python=bool(py_path),
        python_path=py_path,
        has_cpp=bool(cpp_path),
        cpp_path=cpp_path,
        match_strategy=strategy
    )


def read_rows_from_csv(csv_path: Path) -> List[dict]:
    if pd is not None:
        df = pd.read_csv(csv_path)
        return df.to_dict(orient="records")
    out = []
    with csv_path.open("r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            out.append(row)
    return out


def ensure_sqlite(db_path: Path):
    conn = sqlite3.connect(db_path.as_posix())
    cur = conn.cursor()
    cur.execute(
        """
        CREATE TABLE IF NOT EXISTS matches (
            frontend_id TEXT,
            title TEXT,
            title_slug TEXT,
            created_at_approx TEXT,
            difficulty TEXT,
            has_python INTEGER,
            python_path TEXT,
            has_cpp INTEGER,
            cpp_path TEXT,
            match_strategy TEXT,
            PRIMARY KEY (frontend_id, title_slug)
        )
        """
    )
    conn.commit()
    conn.close()


def write_sqlite(db_path: Path, matches: List[MatchResult]):
    conn = sqlite3.connect(db_path.as_posix())
    cur = conn.cursor()
    cur.executemany(
        "REPLACE INTO matches VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)",
        [
            (
                m.frontend_id, m.title, m.title_slug, m.created_at_approx, m.difficulty,
                1 if m.has_python else 0, m.python_path,
                1 if m.has_cpp else 0, m.cpp_path, m.match_strategy
            )
            for m in matches
        ]
    )
    conn.commit()
    conn.close()


def write_csv(csv_path: Path, matches: List[MatchResult]):
    with csv_path.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow([
            "frontend_id","title","title_slug","created_at_approx","difficulty",
            "has_python","python_path","has_cpp","cpp_path","match_strategy"
        ])
        for m in matches:
            w.writerow([
                m.frontend_id, m.title, m.title_slug, m.created_at_approx, m.difficulty,
                int(m.has_python), m.python_path or "", int(m.has_cpp), m.cpp_path or "", m.match_strategy
            ])


def mirror_files(mirror_dir: Path, kamyu_root: Path, matches: List[MatchResult]):
    mirror_dir.mkdir(parents=True, exist_ok=True)
    for m in tqdm(matches, desc="Mirroring matches"):
        if not (m.has_python or m.has_cpp):
            continue
        slug = m.title_slug or _norm(m.title) or f"id-{m.frontend_id or 'unknown'}"
        fid = (m.frontend_id or "").zfill(4) if (m.frontend_id or "").isdigit() else (m.frontend_id or "unknown")
        out_dir = mirror_dir / f"{fid}__{slug}"
        out_dir.mkdir(parents=True, exist_ok=True)
        if m.has_python and m.python_path:
            src = kamyu_root / m.python_path
            (out_dir / "python").mkdir(exist_ok=True)
            try:
                shutil.copy2(src, out_dir / "python" / Path(m.python_path).name)
            except Exception as e:
                (out_dir / "COPY_ERRORS.txt").write_text(f"Python copy failed: {src}\n{e}\n", encoding="utf-8")
        if m.has_cpp and m.cpp_path:
            src = kamyu_root / m.cpp_path
            (out_dir / "cpp").mkdir(exist_ok=True)
            try:
                shutil.copy2(src, out_dir / "cpp" / Path(m.cpp_path).name)
            except Exception as e:
                (out_dir / "COPY_ERRORS.txt").write_text(f"C++ copy failed: {src}\n{e}\n", encoding="utf-8")
        # manifest
        (out_dir / "manifest.json").write_text(
            json.dumps(asdict(m), ensure_ascii=False, indent=2), encoding="utf-8"
        )


def main():
    ap = argparse.ArgumentParser(description="Cross-reference whiskwhite problems CSV with Kamyu solutions repo.")
    ap.add_argument("--kamyu-dir", required=True, help="Path to the local clone of kamyu104/LeetCode-Solutions")
    ap.add_argument("--in-csv", required=True, help="CSV produced by pull_whiskwhite_problems_v2.py")
    ap.add_argument("--out-csv", default="crossref_kamyu.csv", help="Output CSV filepath")
    ap.add_argument("--out-db", default="crossref_kamyu.db", help="Output SQLite DB filepath")
    ap.add_argument("--mirror-dir", default=None, help="Optional directory to copy matched files into")
    ap.add_argument("--languages", default="python,cpp", help="Which languages to index in Kamyu: python,cpp")
    ap.add_argument("--limit", type=int, default=0, help="Optional limit for debugging")
    args = ap.parse_args()

    kamyu_dir = Path(os.path.expanduser(args.kamyu_dir)).resolve()
    if not kamyu_dir.exists():
        raise SystemExit(f"Kamyu dir not found: {kamyu_dir}")

    csv_in = Path(args.in_csv).resolve()
    if not csv_in.exists():
        raise SystemExit(f"Input CSV not found: {csv_in}")

    langs = [x.strip().lower() for x in args.languages.split(",") if x.strip()]
    use_py = "python" in langs
    use_cpp = "cpp" in langs

    print(f"[1/5] Reading problems: {csv_in}")
    rows = read_rows_from_csv(csv_in)
    if args.limit and args.limit > 0:
        rows = rows[: args.limit]
    total = len(rows)
    print(f"  -> {total} problems loaded")

    print(f"[2/5] Indexing Kamyu repo @ {kamyu_dir}")
    idx_py = index_kamyu(kamyu_dir, "python") if use_py else KamyuIndex({}, {}, [])
    idx_cpp = index_kamyu(kamyu_dir, "cpp") if use_cpp else KamyuIndex({}, {}, [])
    print(f"  -> Python files: {len(idx_py.all_paths) if use_py else 0}")
    print(f"  -> C++ files   : {len(idx_cpp.all_paths) if use_cpp else 0}")

    print(f"[3/5] Matching ...")
    matches: List[MatchResult] = []
    for r in tqdm(rows):
        matches.append(find_match(r, idx_py, idx_cpp))

    print(f"[4/5] Writing outputs ...")
    out_csv = Path(args.out_csv).resolve()
    out_db = Path(args.out_db).resolve()
    out_csv.parent.mkdir(parents=True, exist_ok=True)
    out_db.parent.mkdir(parents=True, exist_ok=True)

    write_csv(out_csv, matches)
    ensure_sqlite(out_db)
    write_sqlite(out_db, matches)
    print(f"  -> CSV: {out_csv}")
    print(f"  -> DB : {out_db}")

    print(f"[5/5] Summary")
    any_lang = sum(1 for m in matches if m.has_python or m.has_cpp)
    both = sum(1 for m in matches if m.has_python and m.has_cpp)
    only_py = sum(1 for m in matches if m.has_python and not m.has_cpp)
    only_cpp = sum(1 for m in matches if m.has_cpp and not m.has_python)
    none = total - any_lang

    pct = (any_lang / total * 100) if total else 0.0
    pct_both = (both / total * 100) if total else 0.0

    print(f"  Total problems: {total}")
    print(f"  Matched any   : {any_lang} ({pct:.1f}%)")
    print(f"  Matched both  : {both} ({pct_both:.1f}%)")
    print(f"   - only Python: {only_py}")
    print(f"   - only C++   : {only_cpp}")
    print(f"  Unmatched     : {none}")

    if args.mirror_dir:
        mirror_dir = Path(args.mirror_dir).resolve()
        print(f"  Mirroring matched files -> {mirror_dir}")
        mirror_files(mirror_dir, kamyu_dir, matches)
        print("  Mirror complete.")

    # Write a compact JSON summary next to CSV
    summary_path = out_csv.with_suffix(".summary.json")
    summary = {
        "total": total,
        "matched_any": any_lang,
        "matched_both": both,
        "only_python": only_py,
        "only_cpp": only_cpp,
        "unmatched": none,
    }
    summary_path.write_text(json.dumps(summary, indent=2), encoding="utf-8")
    print(f"  -> Summary JSON: {summary_path}")

    # Print first few unmatched to help manual inspection
    unmatched_preview = [m for m in matches if not (m.has_python or m.has_cpp)][:15]
    if unmatched_preview:
        print("\nFirst few unmatched (up to 15):")
        for m in unmatched_preview:
            print(f"  - [{m.frontend_id}] {m.title}  (slug={m.title_slug})")
    print("\nDone.")

if __name__ == "__main__":
    main()
