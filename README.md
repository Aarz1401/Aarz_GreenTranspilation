# Aarz Green Transpilation

End-to-end workflow for building a Python ↔ C++ problem database, verifying
solutions on LeetCode, and generating AI-assisted translations.

---

## 1. Environment

```bash
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
```

## 2. Fetch problems

```bash
# CSV only
python pull_whiskwhite_problems_v2.py \
  --date-after 2024-05-31 \
  --out-csv whisk_problems.csv

# Hard problems + per-problem folders
python pull_whiskwhite_problems_v2.py \
  --date-after 2024-05-31 \
  --difficulty Hard \
  --out-csv whisk_hard_after_may2024.csv \
  --out-dir whisk_meta

# Quick sample
python pull_whiskwhite_problems_v2.py \
  --date-after 2024-05-31 \
  --limit 50 \
  --out-csv whisk_subset.csv
```

## 3. Cross-reference with Kamyu solutions

```bash
python crossref_from_csv.py \
  --kamyu-dir "/Users/aadil/Aarz_GreenTranspilation/LeetCode-Solutions" \
  --in-csv whisk_hard_after_may2024.csv \
  --out-csv crossref_hard_kamyu.csv \
  --out-db crossref_hard_kamyu.db \
  --mirror-dir kamyu_hard_mirror
```

## 4. Submit/verify solutions

```bash
# Single submission
python src/verify_on_leetcode.py \
  --slug two-sum \
  --lang python3 \
  --code-file path/to/Two_Sum.py \
  --cookies leetcode_cookies_csrftoken.json

# Batch verify Python 2
python src/batch_verify_python.py \
  --root kamyu_hard_mirror \
  --cookies leetcode_cookies_csrftoken.json \
  --out-csv data/batch_verify_results_py2.csv \
  --sleep 12 --max-retries 4 --backoff 20

# Batch verify C++
python src/batch_verify_cpp.py \
  --root kamyu_hard_mirror \
  --cookies leetcode_cookies_csrftoken.json \
  --out-csv data/batch_verify_results_cpp.csv \
  --sleep 12 --max-retries 4 --backoff 20
```

## 5. Summarise passing Python 2 runs

```bash
source .venv/bin/activate
python src/list_passed_python2.py \
  --results-csv data/batch_verify_results_py2.csv \
  --crossref-csv crossref_hard_kamyu.csv \
  --out-csv data/passed_python2.csv \
  --out-md data/passed_python2.md
```

## 6. Translate Python 2 → C++ with GPT

```bash
source .venv/bin/activate
python translate_py2_to_cpp.py \
  --root kamyu_hard_mirror \
  --out-subdir cpp_gpt \
  --model gpt-5-2025-08-07 \
  --global-out-dir cpp_gpt_all \
  --slugs-csv data/passed_python2.csv \
  --csv-out data/translated_cpp_index.csv \
  --max-output-tokens 8192 \
  --overwrite
```

> Adjust `--limit`, `--slug`, or `--overwrite` to control translation scope. Use `--slugs-csv` to target the exact set of verified slugs (for example `data/passed_python2.csv`). `--csv-out` creates an index CSV with the Python and generated C++ paths. Use `--global-out-dir` when you also want a consolidated copy outside the mirror tree. Increase `--max-output-tokens` if you see truncated responses.

## 7. Verify GPT-generated C++ solutions

```bash
source .venv/bin/activate
python src/batch_verify_gpt_cpp.py \
  --root kamyu_hard_mirror \
  --cookies leetcode_cookies_csrftoken.json \
  --out-csv data/test_passing_solution_generated_by_GPT.csv \
  --sleep 15
```

> This tests all GPT-generated C++ files in `kamyu_hard_mirror/*/cpp_gpt/` against LeetCode and tracks pass/fail statistics in a comprehensive CSV with runtime and memory usage data.


NOTES: 
- GPT-5 cutoff date is September 2024, GPT-5-mini cutoff date is May 31st 2024
