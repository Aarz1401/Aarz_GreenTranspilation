# Install deps (if not already)

pip install -r requirements.txt

# Run to fetch hard only problems

# A) Minimal: CSV only (no folders)

python pull_whiskwhite_problems_v2.py \
 --date-after 2024-05-31 \
 --out-csv whisk_problems.csv

# B) Hard-only + per-problem meta folders

python pull_whiskwhite_problems_v2.py \
 --date-after 2024-05-31 \
 --difficulty Hard \
 --out-csv whisk_hard_after_may2024.csv \
 --out-dir whisk_meta

# C) Quick dry run

python pull_whiskwhite_problems_v2.py \
 --date-after 2024-05-31 \
 --limit 50 \
 --out-csv whisk_subset.csv

# Run the crossreferencing script

# Example: use your hard-only CSV produced earlier

python crossref_from_csv.py \
 --kamyu-dir "/Users/aadil/Aarz_GreenTranspilation/LeetCode-Solutions" \
 --in-csv whisk_hard_after_may2024.csv \
 --out-csv crossref_hard_kamyu.csv \
 --out-db crossref_hard_kamyu.db \
 --mirror-dir kamyu_hard_mirror

# Run the verifier script for single file

python verify_on_leetcode.py \
 --slug two-sum \
 --lang python3 \
 --code-file path/to/Two_Sum.py \
 --cookies leetcode_cookies_csrftoken.json

# Usage of Batch_verify

python batch_verify_on_leetcode.py \
 --root kamyu_hard_mirror \
 --verify-script ./verify_on_leetcode.py \
 --cookies leetcode_cookies_csrftoken.json \
 --out-csv batch_verify_results_py2.csv \
 --sleep 12 --max-retries 4 --backoff 20
