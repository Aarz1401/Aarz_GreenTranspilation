#!/usr/bin/env python3
"""
Submit code to LeetCode and poll for the result.

Auth: use your logged-in browser cookies (LEETCODE_SESSION + csrftoken).
Put them in a JSON file like:
{
  "cookies": {"LEETCODE_SESSION": "...", "csrftoken": "..."},
  "csrf_token": "..."
}

Usage
-----
python verify_on_leetcode.py \
  --slug two-sum \
  --lang python3 \
  --code-file path/to/solution.py \
  --cookies leetcode_cookies_csrftoken.json

# Or verify C++:
python verify_on_leetcode.py --slug two-sum --lang cpp --code-file foo.cpp --cookies leetcode_cookies_csrftoken.json
"""
import argparse, json, os, sys, time
from pathlib import Path
from typing import Dict, Any, Optional

import requests

LEETCODE_ORIGIN = "https://leetcode.com"

GRAPHQL_URL = f"{LEETCODE_ORIGIN}/graphql/"
SUBMIT_URL   = f"{LEETCODE_ORIGIN}/problems/{{slug}}/submit/"
CHECK_URL    = f"{LEETCODE_ORIGIN}/submissions/detail/{{submission_id}}/check/"

# GraphQL query to fetch questionId from slug
QUESTION_ID_QUERY = {
    "operationName": "questionData",
    "query": """
    query questionData($titleSlug: String!) {
      question(titleSlug: $titleSlug) {
        questionId
      }
    }
    """,
    "variables": {"titleSlug": None},
}


def load_cookies(path: Path) -> Dict[str, Any]:
    data = json.loads(path.read_text(encoding="utf-8"))
    cookies = data.get("cookies") or {}
    csrf = data.get("csrf_token") or cookies.get("csrftoken")
    if not cookies or not csrf:
        raise SystemExit("cookies/csrf_token missing in cookies JSON.")
    return {"cookies": cookies, "csrf_token": csrf}


def build_session(cookies: Dict[str, str]) -> requests.Session:
    s = requests.Session()
    # set cookies onto the session
    for k, v in cookies.items():
        s.cookies.set(k, v, domain=".leetcode.com")
    # default headers
    s.headers.update({
        "Origin": LEETCODE_ORIGIN,
        "Referer": LEETCODE_ORIGIN + "/",
        "User-Agent": "Mozilla/5.0 (+verify_on_leetcode.py)"
    })
    return s


def get_question_id(session: requests.Session, csrf: str, slug: str) -> str:
    payload = QUESTION_ID_QUERY.copy()
    payload["variables"] = {"titleSlug": slug}
    headers = {
        "x-csrftoken": csrf,
        "content-type": "application/json",
        "referer": f"{LEETCODE_ORIGIN}/problems/{slug}/",
    }
    r = session.post(GRAPHQL_URL, headers=headers, data=json.dumps(payload))
    r.raise_for_status()
    data = r.json()
    q = (data.get("data") or {}).get("question") or {}
    qid = q.get("questionId")
    if not qid:
        raise RuntimeError(f"Could not resolve questionId for slug={slug}: {data}")
    return str(qid)


def submit_code(session: requests.Session, csrf: str, slug: str, qid: str, lang: str, code: str) -> str:
    url = SUBMIT_URL.format(slug=slug)
    headers = {
        "x-csrftoken": csrf,
        "content-type": "application/json",
        "referer": f"{LEETCODE_ORIGIN}/problems/{slug}/",
    }
    payload = {
        "question_id": qid,
        "lang": lang,          # e.g. "python3" or "cpp"
        "typed_code": code,
    }
    r = session.post(url, headers=headers, data=json.dumps(payload))
    r.raise_for_status()
    j = r.json()
    sub_id = j.get("submission_id")
    if not sub_id:
        raise RuntimeError(f"No submission_id in response: {j}")
    return str(sub_id)


def poll_result(session: requests.Session, csrf: str, submission_id: str, timeout_s: int = 120, poll_ms: int = 1000) -> Dict[str, Any]:
    url = CHECK_URL.format(submission_id=submission_id)
    headers = {
        "x-requested-with": "XMLHttpRequest",
        "x-csrftoken": csrf,
        "referer": LEETCODE_ORIGIN + "/",
    }
    # Poll until "state": "SUCCESS" or timeout
    start = time.time()
    while True:
        r = session.get(url, headers=headers)
        r.raise_for_status()
        j = r.json()
        state = j.get("state")
        if state == "SUCCESS":
            return j
        if time.time() - start > timeout_s:
            raise TimeoutError(f"Timed out waiting for result, last payload: {j}")
        time.sleep(poll_ms / 1000.0)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--slug", required=True, help="e.g. two-sum")
    ap.add_argument("--lang", required=True, help="leetcode language key: python3, cpp, java, etc.")
    ap.add_argument("--code-file", required=True, help="path to source file to submit")
    ap.add_argument("--cookies", required=True, help="JSON file with cookies + csrf_token")
    ap.add_argument("--print-json", action="store_true", help="print full result JSON")
    args = ap.parse_args()

    code = Path(args.code_file).read_text(encoding="utf-8")
    auth = load_cookies(Path(args.cookies))
    session = build_session(auth["cookies"])

    # 1) get question id from slug
    qid = get_question_id(session, auth["csrf_token"], args.slug)

    # 2) submit
    sub_id = submit_code(session, auth["csrf_token"], args.slug, qid, args.lang, code)

    # 3) poll
    result = poll_result(session, auth["csrf_token"], sub_id)

    # Pretty summary
    summary = {
        "slug": args.slug,
        "lang": args.lang,
        "question_id": qid,
        "submission_id": sub_id,
        "status_msg": result.get("status_msg"),
        "run_success": result.get("run_success"),
        "total_correct": result.get("total_correct"),
        "total_testcases": result.get("total_testcases"),
        "status_runtime": result.get("status_runtime"),
        "status_memory": result.get("status_memory"),
        "runtime_percentile": result.get("runtime_percentile"),
        "memory_percentile": result.get("memory_percentile"),
        "state": result.get("state"),
    }
    print(json.dumps(summary if not args.print_json else result, indent=2))


if __name__ == "__main__":
    main()