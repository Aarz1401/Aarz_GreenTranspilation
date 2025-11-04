import os
from openai import OpenAI
from dotenv import load_dotenv
import re

load_dotenv()
client = OpenAI(api_key=os.getenv("GPT_API_KEY"))

ROOT_DIR = "new_transpiled_solutions"  
MAIN_SUFFIX = "_main.cpp"              
PY2_SUFFIX = ".py"                     
OUTPUT_SUFFIX = "_with_tests.py"       
MODEL_NAME = "gpt-5-2025-08-07"

def extract_main_content(file_path):
    """Return everything inside int main() { ... }"""
    with open(file_path, "r", encoding="utf-8") as f:
        content = f.read()
    match = re.search(r'int\s+main\s*\(\s*\)\s*{([\s\S]*?)}\s*$', content)
    if match:
        return match.group(1)
    return None

def cpp_main_to_python2(main_code, slug):
    prompt = f"""
You are an expert competitive programmer.
Here is a C++ main() function containing benchmark test cases:

{main_code}

Please convert these test cases into Python2 code that can be run with the original Python2 solution.
- Return only valid Python2 code for generating the inputs.
- Preserve the test cases exactly as in C++.
- Include all necessary variable assignments or lists so the Python2 file can run them directly.
- Do NOT include explanations or extra text.
"""
    response = client.chat.completions.create(
        model=MODEL_NAME,
        messages=[
            {"role": "system", "content": "You convert C++ benchmark test cases into runnable Python2 code."},
            {"role": "user", "content": prompt}
        ]
    )
    return response.choices[0].message.content.strip()

def embed_tests_into_py2(py2_code, test_code, slug):
    prompt = f"""
    You are an expert competitive programmer.
    Here is a Python2 solution for a LeetCode problem:
    ```python
    {py2_code}
    Here are test cases in Python2 format to be added:
    {test_code}
    Please merge these test cases into the Python2 solution so that it can run them automatically.
    Place them in a proper if __name__ == "__main__": block.
    Keep the original solution code intact.
    Do not change function/class signatures.
    Return a single runnable Python2 source file with the test cases included.
    Do NOT include explanations or extra text.
    """
    response = client.chat.completions.create(
    model=MODEL_NAME,
    messages=[
    {"role": "system", "content": "You embed Python2 test cases into a Python2 solution."},
    {"role": "user", "content": prompt}
    ]
    )
    return response.choices[0].message.content.strip()

def main():
    total_files = 0
    generated = 0
    skipped = 0
    failed = 0

    for root, dirs, files in os.walk(ROOT_DIR):
        for file in files:
            if not file.endswith(PY2_SUFFIX) or file.endswith(OUTPUT_SUFFIX):
                continue

            py2_path = os.path.join(root, file)
            slug = file.replace(PY2_SUFFIX, "")
            cpp_main_path = os.path.join(root, slug + MAIN_SUFFIX)
            output_path = os.path.join(root, slug + OUTPUT_SUFFIX)

            # Skip if output already exists
            if os.path.exists(output_path):
                print(f"Skipping {slug} (already has embedded tests)")
                skipped += 1
                continue

            if not os.path.exists(cpp_main_path):
                print(f"No C++ main file found for {slug}")
                failed += 1
                continue

            try:
                main_code = extract_main_content(cpp_main_path)
                if not main_code:
                    print(f"No main() content in {cpp_main_path}")
                    failed += 1
                    continue

                py2_test_code = cpp_main_to_python2(main_code, slug)

                with open(py2_path, "r", encoding="utf-8") as f:
                    py2_code = f.read()

                py2_with_tests = embed_tests_into_py2(py2_code, py2_test_code, slug)

                with open(output_path, "w", encoding="utf-8") as f:
                    f.write(py2_with_tests)

                generated += 1
                print(f"Python2 solution with embedded tests generated for {slug}")

            except Exception as e:
                print(f"Error processing {slug}: {e}")
                failed += 1

# Summary
    print("\n================== SUMMARY ==================")
    print(f"Python2 files scanned:           {total_files}")
    print(f"Embedded test cases generated:   {generated}")
    print(f"Skipped (already exists):        {skipped}")
    print(f"Failed:                          {failed}")
    print("=============================================")


if __name__ == "__main__":
    main()