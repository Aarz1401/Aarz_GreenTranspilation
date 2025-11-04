
#!/usr/bin/env python3

"""
pull_whiskwhite_problems_v2.py
------------------------------

Safer version:
- Correctly parses --date-after via args.date_after
- Handles missing --out-dir (skips meta folders cleanly)
- Clearer logging and counts

Install:
    pip install datasets pandas python-dateutil tqdm pyarrow

Examples:
    python pull_whiskwhite_problems_v2.py --date-after 2024-05-31 --out-csv whisk_problems.csv
    python pull_whiskwhite_problems_v2.py --date-after 2024-05-31 --difficulty Hard --out-csv whisk_hard.csv --out-dir whisk_meta
"""

import argparse
import datetime as dt
import json
from dataclasses import dataclass, asdict
from pathlib import Path
from typing import List, Optional

from datasets import load_dataset  # type: ignore
from dateutil.parser import isoparse  # type: ignore
from tqdm import tqdm  # type: ignore


@dataclass
class ProblemRow:
    frontend_id: str
    id: str
    title: str
    title_slug: str
    url: str
    created_at_approx: str  # YYYY-MM-DD
    difficulty: str
    likes: int
    dislikes: int
    topic_tags: List[str]
    example_test_cases: Optional[str] = None


def _to_date_string(x) -> Optional[str]:
    if x is None:
        return None
    try:
        if hasattr(x, "to_pydatetime"):
            return x.to_pydatetime().date().isoformat()
        if hasattr(x, "date"):
            return x.date().isoformat()
        return isoparse(str(x)).date().isoformat()
    except Exception:
        s = str(x)
        return s[:10] if len(s) >= 10 else None


def main():
    ap = argparse.ArgumentParser(description="Pull problems from whiskwhite/leetcode-complete with filters.")
    ap.add_argument("--date-after", dest="date_after", default="2024-09-30",
                    help="Keep problems strictly AFTER this date (YYYY-MM-DD). Default: 2024-09-30")
    ap.add_argument("--difficulty", default=None,
                    help="Comma-separated subset of difficulties (e.g., Hard or Hard,Medium). Default: all")
    ap.add_argument("--out-csv", default="whisk_problems.csv", help="CSV output filepath")
    ap.add_argument("--out-jsonl", default=None, help="Optional JSONL output filepath")
    ap.add_argument("--out-dir", default=None, help="Optional folder to write per-problem meta.json files")
    ap.add_argument("--limit", type=int, default=0, help="Optional limit for debugging")
    args = ap.parse_args()

    difficulties = None
    if args.difficulty:
        difficulties = {d.strip() for d in args.difficulty.split(",") if d.strip()}

    cutoff = dt.date.fromisoformat(args.date_after)

    print(f"[1/3] Loading Hugging Face dataset: whiskwhite/leetcode-complete ...")
    ds = load_dataset("whiskwhite/leetcode-complete", split="train")
    total = len(ds) if hasattr(ds, "__len__") else None
    if total is not None:
        print(f"  -> {total} rows loaded")

    print("[2/3] Filtering rows ...")
    rows: List[ProblemRow] = []
    kept_by_diff = 0
    for rec in tqdm(ds):
        created = _to_date_string(rec.get("created_at_approx"))
        if not created:
            continue
        try:
            created_date = dt.date.fromisoformat(created)
        except Exception:
            continue
        if created_date <= cutoff:
            continue

        diff = rec.get("difficulty") or ""
        if difficulties and diff not in difficulties:
            continue
        kept_by_diff += 1

        pr = ProblemRow(
            frontend_id=str(rec.get("frontend_id") or ""),
            id=str(rec.get("id") or ""),
            title=str(rec.get("title") or ""),
            title_slug=str(rec.get("title_slug") or ""),
            url=str(rec.get("url") or ""),
            created_at_approx=created,
            difficulty=diff,
            likes=int(rec.get("likes") or 0),
            dislikes=int(rec.get("dislikes") or 0),
            topic_tags=list(rec.get("topic_tags") or []),
            example_test_cases=rec.get("example_test_cases"),
        )
        rows.append(pr)

        if args.limit and len(rows) >= args.limit:
            break

    print(f"  -> kept {len(rows)} problems strictly after {cutoff}"
          + (f" with difficulties {sorted(difficulties)}" if difficulties else ""))

    print("[3/3] Writing outputs ...")
    # CSV
    import csv
    out_csv = Path(args.out_csv)
    out_csv.parent.mkdir(parents=True, exist_ok=True)
    with out_csv.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow([
            "frontend_id","id","title","title_slug","url",
            "created_at_approx","difficulty","likes","dislikes",
            "topic_tags","example_test_cases"
        ])
        for r in rows:
            w.writerow([
                r.frontend_id, r.id, r.title, r.title_slug, r.url,
                r.created_at_approx, r.difficulty, r.likes, r.dislikes,
                ";".join(r.topic_tags),
                (r.example_test_cases or "").replace("\n", "\\n")
            ])
    print(f"  -> CSV: {out_csv}")

    # JSONL (optional)
    if args.out_jsonl:
        out_jsonl = Path(args.out_jsonl)
        out_jsonl.parent.mkdir(parents=True, exist_ok=True)
        with out_jsonl.open("w", encoding="utf-8") as f:
            for r in rows:
                f.write(json.dumps(asdict(r), ensure_ascii=False) + "\n")
        print(f"  -> JSONL: {out_jsonl}")

    # Per-problem meta folder (optional)
    if args.out_dir is not None and str(args.out_dir).strip() != "":
        out_dir = Path(args.out_dir)
        out_dir.mkdir(parents=True, exist_ok=True)
        for r in rows:
            slug = r.title_slug or r.title.lower().strip().replace(" ", "-")
            sub = out_dir / f"{r.created_at_approx}__{slug}"
            sub.mkdir(exist_ok=True, parents=True)
            meta_path = sub / "meta.json"
            with meta_path.open("w", encoding="utf-8") as f:
                json.dump(asdict(r), f, ensure_ascii=False, indent=2)
        print(f"  -> meta folders under: {out_dir}")
    else:
        print("  -> no --out-dir provided (skipping meta folders)")

    print("Done.")

if __name__ == "__main__":
    main()
