import os
from openai import OpenAI
from dotenv import load_dotenv
import re
from pathlib import Path


load_dotenv()
client = OpenAI(api_key=os.getenv("GPT_API_KEY"))

PY2_ROOT = "new_transpiled_solutions"     # Python2 source files
CPP_ROOT = "CPP_CLEANED_AFTER"  # C++ main files with test cases
PY2_SUFFIX = ".py"
OUTPUT_SUFFIX = "_benchmark_v3.py"
MODEL_NAME = "gpt-5-2025-08-07"
CPP_MAIN_SUFFIX = "_main_v3.cpp"


GENERATED_SUFFIXES = (
    "_with_tests.py",
    "_benchmark_v2.py",
)

TARGET_SLUGS = {
    "count-beautiful-numbers",
    "manhattan-distances-of-all-arrangements-of-pieces",
    "maximize-spanning-tree-stability-with-upgrades",
    "minimum-increments-for-target-multiples-in-an-array",
    "minimum-operations-to-make-elements-within-k-subarrays-equal",
}

#Extracting main content (test case generated item) from file 
def extract_main_content(file_path):
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
Return only valid Python2 code, preserve the test cases exactly, and include all necessary variable assignments.
Do NOT include explanations or extra text.
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
Here is a Python2 solution:

```python
{py2_code}
```
Here are test cases in Python2 format to be added:
{test_code}

Merge these test cases into the Python2 solution so that it can run automatically.
Place them in a proper if name == "main": block.
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
    for root, dirs, files in os.walk(PY2_ROOT):
        for file in files:
            if not file.endswith(PY2_SUFFIX) or file.endswith(OUTPUT_SUFFIX) or file.endswith("_with_tests.py") or any(file.endswith(sfx) for sfx in GENERATED_SUFFIXES):
                continue


            total_files += 1
            py2_path = os.path.join(root, file)
            slug = file.replace(PY2_SUFFIX, "")

            # Only run selected problems
            # if TARGET_SLUGS and slug not in TARGET_SLUGS:
            #     continue

            # C++ main path
            #cpp_main_path = Path(CPP_ROOT) / slug / f"{slug}_main_v2.cpp"
            cpp_main_path = Path(root) / f"{slug}_main_v3.cpp"
            #cpp_main_path = Path(CPP_ROOT) / slug / f"{slug}_solution_main_v3.cpp"
            output_path = os.path.join(root, slug + OUTPUT_SUFFIX)

            if os.path.exists(output_path):
                print(f"Skipping {slug} (already has embedded tests)")
                skipped += 1
                continue

            if not cpp_main_path.exists():
                print(f"No C++ main file found for {slug} at {cpp_main_path}")
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


    print("\n================== SUMMARY ==================")
    print(f"Python2 files scanned:           {total_files}")
    print(f"Embedded test cases generated:   {generated}")
    print(f"Skipped (already exists):        {skipped}")
    print(f"Failed:                          {failed}")
    print("=============================================")


if __name__ == "__main__":
     main()