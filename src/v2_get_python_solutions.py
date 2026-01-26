
import csv
import os
from openai import OpenAI
from dotenv import load_dotenv

# Adjust these
REPO_PATH = "./LeetCode-Solutions"
CSV_FILE = "batch_verify_results_py3.csv"
OUTPUT_DIR = "new_transpiled_solutions"
LIMIT = 120  # number of problems to process

load_dotenv()

GPT_API = os.getenv('GPT_API_KEY')
client = OpenAI(api_key=GPT_API)

SYSTEM_PROMPT = (
    "You are an elite competitive-programming mentor who fluently translates "
    "LeetCode-style Python 2 solutions into efficient, clean modern C++ (C++17). "
    "Preserve algorithmic intent, helper functions, and comments. Use standard "
    "library facilities that compile on LeetCode. Keep class/function signatures "
    "matching the original problem expectations. Return only runnable C++ source "
    "code—no explanations or tests. CRITICAL: Always include explicit standard "
    "library headers like #include <iostream>, #include <vector>, etc. NEVER use #include <bits/stdc++.h>."
)

USER_TEMPLATE = """Problem slug: {slug}
Python source file: {source_name}

Translate the following Python 2 code into a single C++17 source file suitable
for submitting to LeetCode. Maintain the public class/method signatures expected
by LeetCode. Use only the C++ standard library allowed on LeetCode. Prefer
explicit types, std::vector, std::array, etc.

CRITICAL REQUIREMENT: You MUST include explicit standard library headers at the 
top of your C++ code.
NEVER use #include <bits/stdc++.h> as it will cause compilation errors on LeetCode.

python
{python_code}
"""

def transpile_python_to_cpp(python_code: str, slug: str, source_name: str) -> str:
    user_prompt = USER_TEMPLATE.format(slug=slug, source_name=source_name, python_code=python_code)
    
    response = client.chat.completions.create(
        model="gpt-5-2025-08-07",
        messages=[
            {"role": "system", "content": SYSTEM_PROMPT},
            {"role": "user", "content": user_prompt}
        ]
    )
    return response.choices[0].message.content

def main():
    count = 0
    with open(CSV_FILE, newline="", encoding="utf-8") as f:
        reader = csv.DictReader(f)
        for row in reader:
            if count >= LIMIT:
                break
            
            if row.get("state") != "SUCCESS":
                continue

            python_path = row.get("file")  
            if not python_path:
                continue

            question_id = row["question_id"]
            slug = row["slug"]

            print("=" * 80)
            print(f"Problem: {slug} ({question_id})")
            print(f"Python Path: {python_path}")

            if not os.path.exists(python_path):
                print("Python file not found, skipping")
                continue

            # Read Python code
            with open(python_path, "r", encoding="utf-8") as pf:
                python_code = pf.read()
                print(python_code)

            # -----------------------------
            # GPT API placeholder
            # -----------------------------
            # Here you would send `python_code` to GPT to get the C++ transpiled version
            # For testing, we'll just add a placeholder C++ comment
            gpt_cpp_code = transpile_python_to_cpp(python_code, slug, os.path.basename(python_path))
            # gpt_cpp_code = f"// Transpiled C++ code for {slug}\n"

            # -----------------------------
            # Create output folder structure
            # -----------------------------
            slug_folder = os.path.join(OUTPUT_DIR, f"{question_id}__{slug}")
            cpp_folder = os.path.join(slug_folder, "cpp")
            os.makedirs(cpp_folder, exist_ok=True)

            # Write the C++ file
            cpp_file_path = os.path.join(cpp_folder, f"{slug}.cpp")
            with open(cpp_file_path, "w", encoding="utf-8") as cf:
                cf.write(gpt_cpp_code)

            print(f"✅ Wrote C++ file: {cpp_file_path}\n")

            count += 1

if __name__ == "__main__":
    main()
