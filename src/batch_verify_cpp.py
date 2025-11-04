#!/usr/bin/env python3
"""
Batch-submit C++ files to LeetCode using verify_on_leetcode.py.

- Walks <root>/<id>__<slug>/cpp/*.{cpp,cc,cxx,C}
- Forces --lang cpp on every submission
- Resumable CSV, gentle rate-limiting, 429 backoff

Usage:
  python batch_verify_cpp.py \
    --root kamyu_hard_mirror \
    --verify-script ./verify_on_leetcode.py \
    --cookies leetcode_cookies_csrftoken.json \
    --out-csv batch_verify_results_cpp.csv \
    --sleep 12 --max-retries 4 --backoff 20
"""
import argparse, csv, json, sys, time, subprocess, datetime as dt
from pathlib import Path
from typing import Set, Tuple

CPP_EXTS = (".cpp", ".cc", ".cxx", ".C")

def load_done(out_csv: Path) -> Set[Tuple[str,str]]:
    done=set()
    if out_csv.exists():
        for r in csv.DictReader(open(out_csv, encoding="utf-8")):
            done.add((r.get("slug",""), r.get("file","")))
    return done

def append(out_csv: Path, row: dict):
    out_csv.parent.mkdir(parents=True, exist_ok=True)
    header = ["timestamp","slug","file","lang","status_msg","run_success","total_correct","total_testcases",
              "status_runtime","status_memory","runtime_percentile","memory_percentile","question_id","submission_id","state"]
    exists = out_csv.exists()
    with open(out_csv, "a", newline="", encoding="utf-8") as f:
        w=csv.DictWriter(f, fieldnames=header)
        if not exists: w.writeheader()
        w.writerow({k: row.get(k,"") for k in header})

def parse_slug(problem_dir: Path):
    name = problem_dir.name
    if "__" in name: return name.split("__",1)[1]
    m = problem_dir / "manifest.json"
    if m.exists():
        try: return json.loads(m.read_text(encoding="utf-8")).get("title_slug")
        except: return None
    return None

def run_verify(verify_script: Path, cookies: Path, slug: str, code_file: Path, timeout_s: int=300):
    cmd = [sys.executable, verify_script.as_posix(),
           "--slug", slug, "--lang", "cpp",
           "--code-file", code_file.as_posix(), "--cookies", cookies.as_posix()]
    p = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout_s)
    return p.returncode, p.stdout, p.stderr

def is_429(stdout: str, stderr: str) -> bool:
    blob = (stdout or "") + "\n" + (stderr or "")
    return ("429" in blob) or ("Too Many Requests" in blob)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", required=True, help="Mirror root that contains cpp subfolders")
    ap.add_argument("--verify-script", required=True, help="Path to verify_on_leetcode.py")
    ap.add_argument("--cookies", required=True, help="Cookies JSON with LEETCODE_SESSION + csrftoken")
    ap.add_argument("--out-csv", default="batch_verify_results_cpp.csv")
    ap.add_argument("--sleep", type=float, default=12.0, help="Seconds between submissions")
    ap.add_argument("--max-retries", type=int, default=4, help="Max retries on 429")
    ap.add_argument("--backoff", type=float, default=20.0, help="Extra seconds added per retry level on 429")
    ap.add_argument("--limit", type=int, default=0, help="Max files (0 = all)")
    args = ap.parse_args()

    root = Path(args.root).resolve()
    verify = Path(args.verify_script).resolve()
    cookies = Path(args.cookies).resolve()
    out_csv = Path(args.out_csv).resolve()
    if not root.exists(): raise SystemExit(f"root not found: {root}")
    if not verify.exists(): raise SystemExit(f"verify script not found: {verify}")
    if not cookies.exists(): raise SystemExit(f"cookies file not found: {cookies}")

    done = load_done(out_csv)
    processed = 0

    for prob in sorted([p for p in root.iterdir() if p.is_dir()]):
        slug = parse_slug(prob)
        if not slug:
            print(f"[skip] no slug for {prob.name}")
            continue
        cpp_dir = prob / "cpp"
        if not cpp_dir.exists():
            continue

        for cf in sorted([p for p in cpp_dir.iterdir() if p.is_file() and p.suffix in CPP_EXTS]):
            key=(slug, cf.as_posix())
            if key in done:
                continue

            tries = 0
            while True:
                print(f"-> submit {cf.name} (slug={slug}, lang=cpp) try={tries+1}")
                rc, out, err = run_verify(verify, cookies, slug, cf)
                now = dt.datetime.utcnow().isoformat()+"Z"

                if rc==0:
                    try:
                        j = json.loads(out.strip() or err.strip())
                    except Exception as e:
                        j = {"status_msg": f"ERROR: bad JSON ({e})", "state":"ERROR"}
                    append(out_csv, {
                        "timestamp": now, "slug": slug, "file": cf.as_posix(), "lang": "cpp",
                        "status_msg": str(j.get("status_msg","")),
                        "run_success": str(j.get("run_success","")),
                        "total_correct": str(j.get("total_correct","")),
                        "total_testcases": str(j.get("total_testcases","")),
                        "status_runtime": str(j.get("status_runtime","")),
                        "status_memory": str(j.get("status_memory","")),
                        "runtime_percentile": str(j.get("runtime_percentile","")),
                        "memory_percentile": str(j.get("memory_percentile","")),
                        "question_id": str(j.get("question_id","")),
                        "submission_id": str(j.get("submission_id","")),
                        "state": str(j.get("state",""))
                    })
                    break

                if is_429(out, err) and tries < args.max_retries:
                    delay = args.sleep + args.backoff * (tries+1)
                    print(f"   got 429 -> backing off {delay:.1f}s")
                    time.sleep(delay)
                    tries += 1
                    continue

                append(out_csv, {
                    "timestamp": now, "slug": slug, "file": cf.as_posix(), "lang": "cpp",
                    "status_msg": f"ERROR: verify failed rc={rc}",
                    "run_success":"", "total_correct":"", "total_testcases":"",
                    "status_runtime":"", "status_memory":"", "runtime_percentile":"", "memory_percentile":"",
                    "question_id":"", "submission_id":"", "state":"ERROR"
                })
                break

            processed += 1
            if args.limit and processed >= args.limit:
                print(f"limit {args.limit} reached"); return
            time.sleep(max(0.0, args.sleep))

    print(f"Done. Processed {processed} new file(s). Results -> {out_csv}")

if __name__ == "__main__":
    main()
