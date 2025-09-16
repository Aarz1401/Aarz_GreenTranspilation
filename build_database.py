import os
import time
import csv
import requests
import pandas as pd
from bs4 import BeautifulSoup

# =========================
# CONFIG — CHANGE THIS PATH
# =========================
# e.g., REPO_PATH = "/Users/aadil/code/libs/LeetCode-Solutions"
REPO_PATH = "./LeetCode-Solutions"

CPP_DIR = os.path.join(REPO_PATH, "C++")
PY_DIR  = os.path.join(REPO_PATH, "Python")

OUT_XLSX = "hard_problems_kamyu_with_statements_local.xlsx"
OUT_CSV  = "hard_problems_kamyu_with_statements_local.csv"

LEETCODE_ALL     = "https://leetcode.com/api/problems/all/"
LEETCODE_GRAPHQL = "https://leetcode.com/graphql"

HEADERS = {
    "User-Agent": "kamyu-hard-extractor-local/1.0",
    "Referer": "https://leetcode.com",
}

GRAPHQL_QUERY = """
query questionData($titleSlug: String!) {
  question(titleSlug: $titleSlug) {
    questionId
    title
    difficulty
    content
    isPaidOnly
    questionFrontendId
  }
}
"""

# -------------------------
# Helpers
# -------------------------
def html_to_text(html: str) -> str:
    if not html:
        return ""
    soup = BeautifulSoup(html, "html.parser")
    for br in soup.find_all("br"):
        br.replace_with("\n")
    txt = soup.get_text(separator="\n")
    return "\n".join(line.strip() for line in txt.splitlines() if line.strip())

def load_all_problems():
    for attempt in range(4):
        try:
            r = requests.get(LEETCODE_ALL, headers=HEADERS, timeout=30)
            if r.status_code == 200:
                return r.json()
            time.sleep(0.7 * (attempt + 1))
        except Exception:
            time.sleep(0.7 * (attempt + 1))
    raise RuntimeError("Failed to fetch LeetCode problems list")

def gql_question(slug: str):
    payload = {"query": GRAPHQL_QUERY, "variables": {"titleSlug": slug}}
    for attempt in range(3):
        try:
            r = requests.post(LEETCODE_GRAPHQL, headers={**HEADERS, "Content-Type": "application/json"},
                              json=payload, timeout=30)
            if r.status_code == 200:
                return r.json()
            time.sleep(0.8 * (attempt + 1))
        except Exception:
            time.sleep(0.8 * (attempt + 1))
    return None

def gather_repo_slugs_local():
    if not (os.path.isdir(CPP_DIR) and os.path.isdir(PY_DIR)):
        raise SystemExit(
            f"Local repo not found.\nExpected C++ at: {CPP_DIR}\nExpected Python at: {PY_DIR}\n"
            "Update REPO_PATH at the top of the script."
        )
    cpp_slugs, py_slugs = set(), set()
    for fname in os.listdir(CPP_DIR):
        if fname.endswith(".cpp"):
            cpp_slugs.add(fname[:-4])  # remove .cpp
    for fname in os.listdir(PY_DIR):
        if fname.endswith(".py"):
            py_slugs.add(fname[:-3])   # remove .py
    return cpp_slugs, py_slugs

# -------------------------
# Main
# -------------------------
def main():
    print("Step 1/4: Fetching LeetCode problems list …", flush=True)
    all_data = load_all_problems()
    pairs = all_data["stat_status_pairs"]

    # Keep only Hard
    hard = []
    for e in pairs:
        if e["difficulty"]["level"] == 3:
            s = e["stat"]
            hard.append({
                "id": s["frontend_question_id"],
                "title": s["question__title"],
                "slug": s["question__title_slug"],
                "paid_only": e.get("paid_only", False),
            })
    print(f"  -> Hard problems in LC list: {len(hard)}", flush=True)

    print("Step 2/4: Scanning local repo for C++/Python slugs …", flush=True)
    cpp_slugs, py_slugs = gather_repo_slugs_local()
    print(f"  -> Found C++ solutions: {len(cpp_slugs)}, Python solutions: {len(py_slugs)}", flush=True)

    # Keep only problems that have BOTH C++ and Python solutions locally
    hard_both = [p for p in hard if p["slug"] in cpp_slugs and p["slug"] in py_slugs]
    # Sort by LeetCode ID (approx original posting order)
    hard_both.sort(key=lambda x: int(x["id"]))
    print(f"  -> Hard with BOTH langs: {len(hard_both)}", flush=True)

    print("Step 3/4: Fetching statements via LeetCode GraphQL …", flush=True)
    rows = []
    total = len(hard_both)
    for idx, p in enumerate(hard_both, 1):
        slug = p["slug"]
        # Basic links
        leet_url = f"https://leetcode.com/problems/{slug}/"
        cpp_url  = f"{'file://'+os.path.abspath(os.path.join(CPP_DIR, slug+'.cpp')) if os.path.exists(os.path.join(CPP_DIR, slug+'.cpp')) else ''}"
        py_url   = f"{'file://'+os.path.abspath(os.path.join(PY_DIR, slug+'.py')) if os.path.exists(os.path.join(PY_DIR, slug+'.py')) else ''}"
        # If you prefer GitHub links instead of file://, swap to:
        # cpp_url = f"https://github.com/kamyu104/LeetCode-Solutions/blob/master/C++/{slug}.cpp"
        # py_url  = f"https://github.com/kamyu104/LeetCode-Solutions/blob/master/Python/{slug}.py"

        content_html = ""
        content_text = ""
        difficulty   = "HARD"
        qfid         = str(p["id"])
        is_paid      = p["paid_only"]

        gql = gql_question(slug)
        if gql and isinstance(gql, dict):
            q = (gql.get("data") or {}).get("question")
            if q:
                content_html = q.get("content", "") or ""
                content_text = html_to_text(content_html)
                difficulty   = q.get("difficulty", difficulty) or difficulty
                qfid         = q.get("questionFrontendId", qfid) or qfid
                is_paid      = q.get("isPaidOnly", is_paid)

        rows.append({
            "LeetCode ID": int(qfid),
            "Title": p["title"],
            "Slug": slug,
            "Difficulty": difficulty,
            "Paid Only": bool(is_paid),
            "LeetCode Link": leet_url,
            "C++ Solution (local)": cpp_url,
            "Python Solution (local)": py_url,
            "Statement (HTML)": content_html,
            "Statement (Plain Text)": content_text
        })

        if idx % 20 == 0 or idx == total:
            print(f"  -> {idx}/{total} fetched", flush=True)

        # polite pacing against GraphQL
        time.sleep(0.12)

    print("Step 4/4: Writing XLSX + CSV …", flush=True)
    df = pd.DataFrame(rows).sort_values(["LeetCode ID", "Slug"])
    df.to_excel(OUT_XLSX, index=False)
    df.to_csv(OUT_CSV, index=False, quoting=csv.QUOTE_MINIMAL)

    print(f"Done. Rows: {len(df)}", flush=True)
    print(f"Wrote: {OUT_XLSX} and {OUT_CSV}", flush=True)

if __name__ == "__main__":
    main()