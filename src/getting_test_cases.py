import os
from openai import OpenAI
from dotenv import load_dotenv


load_dotenv()
client = OpenAI(api_key=os.getenv("GPT_API_KEY"))

ROOT_DIR = "new_transpiled_solutions"      # Root directory for C++ solutions
OUTPUT_SUFFIX = "_benchmark_v3.cpp"       # Output file name suffix
MAX_CHARS = 10000                       # Optional truncation limit for long code
ITERATIONS = 1000                      # Number of iterations for the benchmark loop
MODEL_NAME = "gpt-5-2025-08-07"        # GPT model version


def generate_benchmark(cpp_code: str, slug: str, iterations: int):
    truncated_code = cpp_code[:MAX_CHARS] if MAX_CHARS else cpp_code

    prompt = f"""
    REQUIREMENTS:
    1. Generate a C++ benchmark for this solution
    2. Create exactly 10 VALID and diverse test inputs
    3. Run them EXACTLY {iterations} times
    Original C++ solution:
    ```cpp
    {truncated_code}
    ```
    Benchmark rules:

    - Include required headers only
    - Use the Solution class unchanged
    - Store the 10 test inputs in a single container (e.g. vector<string>, vector<vector<int>>, etc.)
    - Use this EXACT loop structure:
      const int iterations = {iterations};
      for (int iter = 0; iter < iterations; ++iter) {{
          // test code
      }}
    - Do NOT include any timing code
    - Do NOT print anything

    Prevent optimization with minimal overhead:
    - declare `volatile int sink = 0;` outside the loop
    - inside the loop declare `int checksum = 0;`
    - accumulate results of the 10 tests into checksum
    - do exactly one volatile write per iteration: `sink = checksum;`
    - do NOT accumulate across iterations

    Input validity:
    - Do NOT include empty or invalid inputs
    - All test inputs must respect the problem constraints

    Return a complete C++ file only, with no explanation outside the code.
    """

    response = client.chat.completions.create(
        model=MODEL_NAME,
        messages=[
            {"role": "system", "content": "You generate minimal, correct C++ benchmark programs."},
            {"role": "user", "content": prompt}
        ]
    )


    return response.choices[0].message.content.strip()

def main():
    total_cpp_files = 0
    generated_benchmarks = 0
    skipped_existing = 0
    failed = 0

    for root, dirs, files in os.walk(ROOT_DIR):
        for file in files:
            #if not file.endswith(".cpp") or file.endswith(OUTPUT_SUFFIX):
            if not file.endswith(".cpp"):
                continue
            if file.endswith("_benchmark.cpp") or file.endswith("_main.cpp") or file.endswith("_benchmark_v2.cpp") or file.endswith("_main_v2.cpp"):
                continue

            total_cpp_files += 1
            cpp_path = os.path.join(root, file)
            slug = os.path.basename(file).replace(".cpp", "")
            output_path = os.path.join(root, slug + OUTPUT_SUFFIX)

            if os.path.exists(output_path):
                print(f"Skipping existing benchmark for: {slug}")
                skipped_existing += 1
                continue

            print(f"\nGenerating benchmark for: {slug}")

            try:
                with open(cpp_path, "r", encoding="utf-8") as f:
                    cpp_code = f.read()

                benchmark_code = generate_benchmark(cpp_code, slug, ITERATIONS)

                with open(output_path, "w", encoding="utf-8") as out:
                    out.write(benchmark_code)

                generated_benchmarks += 1
                print(f"Saved benchmark: {output_path}")

            except Exception as e:
                print(f"Error generating benchmark for {slug}: {e}")
                failed += 1

    # ==============================
    # Summary
    # ==============================
    print("\n================== SUMMARY ==================")
    print(f"Total C++ files scanned:   {total_cpp_files}")
    print(f"Benchmarks generated:      {generated_benchmarks}")
    print(f"Skipped (already exists):  {skipped_existing}")
    print(f"Failed generations:        {failed}")
    print("=============================================")


if __name__ == "__main__":
    main()
