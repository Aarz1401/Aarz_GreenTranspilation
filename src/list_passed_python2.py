#!/usr/bin/env python3
"""Summarise passing Python 2 submissions from batch verification.

Example usage
-------------
python src/list_passed_python2.py \
  --results-csv batch_verify_results_py2.csv \
  --crossref-csv crossref_hard_kamyu.csv \
  --out-csv passed_python2.csv

The script expects the CSV emitted by ``src/batch_verify_python.py`` (or the
root-level ``batch_verify_on_leetcode.py``). Rows with ``status_msg`` equal to
"Accepted" (case-insensitive), ``state`` equal to ``SUCCESS`` and
``run_success`` truthy are considered passing submissions.
"""
from __future__ import annotations

import argparse
import csv
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, Iterable, List, Optional, Tuple

PASS_STATUS = {"accepted"}
PASS_STATE = {"success"}
TRUTHY = {"true", "1", "yes", "y"}


@dataclass
class ResultRow:
    slug: str
    file: str
    status_msg: str
    state: str
    run_success: str
    runtime: str
    memory: str
    question_id: str
    submission_id: str


@dataclass
class CrossRefRow:
    frontend_id: str
    title: str
    slug: str
    difficulty: str
    python_path: str
    created_at: str


def read_results(csv_path: Path) -> Iterable[ResultRow]:
    with csv_path.open("r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            yield ResultRow(
                slug=(row.get("slug") or "").strip(),
                file=(row.get("file") or "").strip(),
                status_msg=(row.get("status_msg") or "").strip(),
                state=(row.get("state") or "").strip(),
                run_success=(row.get("run_success") or "").strip(),
                runtime=(row.get("status_runtime") or "").strip(),
                memory=(row.get("status_memory") or "").strip(),
                question_id=(row.get("question_id") or "").strip(),
                submission_id=(row.get("submission_id") or "").strip(),
            )


def read_crossref(csv_path: Path) -> Dict[str, CrossRefRow]:
    mapping: Dict[str, CrossRefRow] = {}
    with csv_path.open("r", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            slug = (row.get("title_slug") or "").strip()
            if not slug:
                continue
            mapping[slug] = CrossRefRow(
                frontend_id=(row.get("frontend_id") or "").strip(),
                title=(row.get("title") or "").strip(),
                slug=slug,
                difficulty=(row.get("difficulty") or "").strip(),
                python_path=(row.get("python_path") or "").strip(),
                created_at=(row.get("created_at_approx") or "").strip(),
            )
    return mapping


def is_passing(row: ResultRow) -> bool:
    if not row.slug or not row.file:
        return False
    if row.status_msg.lower() not in PASS_STATUS:
        return False
    if row.state.lower() not in PASS_STATE:
        return False
    if row.run_success and row.run_success.lower() not in TRUTHY and row.run_success.lower() not in PASS_STATUS:
        return False
    return True


def unique_passes(rows: Iterable[ResultRow]) -> Dict[Tuple[str, str], ResultRow]:
    latest: Dict[Tuple[str, str], ResultRow] = {}
    for row in rows:
        key = (row.slug, row.file)
        latest[key] = row
    return latest


def write_output(
    rows: List[Tuple[ResultRow, Optional[CrossRefRow]]],
    out_csv: Optional[Path],
    out_md: Optional[Path],
):
    if out_csv:
        out_csv.parent.mkdir(parents=True, exist_ok=True)
        with out_csv.open("w", newline="", encoding="utf-8") as f:
            writer = csv.writer(f)
            writer.writerow([
                "slug",
                "title",
                "difficulty",
                "created_at",
                "python_path",
                "file",
                "runtime",
                "memory",
                "question_id",
                "submission_id",
            ])
            for result, meta in rows:
                writer.writerow([
                    result.slug,
                    meta.title if meta else "",
                    meta.difficulty if meta else "",
                    meta.created_at if meta else "",
                    meta.python_path if meta else "",
                    result.file,
                    result.runtime,
                    result.memory,
                    result.question_id,
                    result.submission_id,
                ])

    if out_md:
        out_md.parent.mkdir(parents=True, exist_ok=True)
        with out_md.open("w", encoding="utf-8") as f:
            f.write("| Slug | Title | Difficulty | Created | File | Runtime | Memory |\n")
            f.write("| --- | --- | --- | --- | --- | --- | --- |\n")
            for result, meta in rows:
                f.write(
                    f"| {result.slug} | {meta.title if meta else ''} | {meta.difficulty if meta else ''} | "
                    f"{meta.created_at if meta else ''} | {Path(result.file).name} | {result.runtime} | {result.memory} |\n"
                )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--results-csv", required=True, help="CSV output from batch_verify_python")
    parser.add_argument("--crossref-csv", help="Optional crossref CSV to enrich rows")
    parser.add_argument("--out-csv", help="Optional CSV file to write passed rows")
    parser.add_argument("--out-md", help="Optional Markdown summary table")
    return parser.parse_args()


def main() -> int:
    args = parse_args()

    results_path = Path(args.results_csv).resolve()
    if not results_path.exists():
        raise SystemExit(f"Results CSV not found: {results_path}")

    crossref_path = Path(args.crossref_csv).resolve() if args.crossref_csv else None
    crossref_map = read_crossref(crossref_path) if crossref_path else {}

    passes = [row for row in unique_passes(read_results(results_path)).values() if is_passing(row)]
    def sort_key(row: ResultRow) -> Tuple:
        meta = crossref_map.get(row.slug) if crossref_map else None
        created = meta.created_at if meta else ""
        return (created or "", row.slug, row.file)

    passes.sort(key=sort_key)

    enriched: List[Tuple[ResultRow, Optional[CrossRefRow]]] = []
    for row in passes:
        meta = crossref_map.get(row.slug) if crossref_map else None
        enriched.append((row, meta))

    out_csv = Path(args.out_csv).resolve() if args.out_csv else None
    out_md = Path(args.out_md).resolve() if args.out_md else None

    write_output(enriched, out_csv, out_md)

    print(f"Passing Python 2 solutions: {len(enriched)}")
    for result, meta in enriched[:20]:
        title = f" - {meta.title}" if meta and meta.title else ""
        created = f" [{meta.created_at}]" if meta and meta.created_at else ""
        print(f"  {result.slug}{title}{created} -> {Path(result.file).name}")
    if len(enriched) > 20:
        print("  ...")

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
