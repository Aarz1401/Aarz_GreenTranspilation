import os
from openai import OpenAI
from dotenv import load_dotenv

load_dotenv()
client = OpenAI(api_key=os.getenv("GPT_API_KEY"))

ROOT_DIR = "new_transpiled_solutions"  
OUTPUT_SUFFIX = "_benchmark.cpp"       
MAX_CHARS = 6000                       
ITERATIONS = 1000                      
MODEL_NAME = "gpt-5-2025-08-07"        



def generate_benchmark(cpp_code: str, slug: str, iterations: int):
    """Ask GPT to create a benchmark C++ file for the given solution."""
    truncated_code = cpp_code[:MAX_CHARS] if MAX_CHARS else cpp_code

    prompt = f"""
    REQUIREMENTS:
    1. Create a benchmark that generates 10 diverse test inputs for this solution
    2. The benchmark should run these inputs in a loop EXACTLY {iterations} times
    3. Use high_resolution_clock to measure and report the execution time

    Here's the original C++ solution to analyze:

    ```cpp
    {truncated_code}
    The benchmark should:

    Include all necessary headers (including <chrono> for timing)
    Define 10 different test inputs that cover various cases (number arrays, strings, etc., as required by the solution)
    Run the main test function in a loop EXACTLY {iterations} times using this EXACT pattern:
    const int iterations = {iterations};
    for (int iter = 0; iter < iterations; ++iter) {{
        // test code here
    }}


    Use std::chrono::high_resolution_clock to measure execution time
    Use the Solution class from the original code without modification
    Use a checksum or accumulator variable to ensure the compiler doesn't optimize away the calculations
    Print the result/checksum and elapsed time at the end
    IMPORTANT: The for loop MUST use this exact style:
    Declare const int iterations = {iterations}; before the loop
    Loop condition: iter < iterations (NOT iter < {iterations} directly)
    Use ++iter for increment
    Format your response as a complete C++ file with no additional explanation outside the code.
    """

    response = client.chat.completions.create(
        model=MODEL_NAME,
        messages=[
            {"role": "system", "content": "You generate high-quality C++ benchmark programs for LeetCode-style problems."},
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
            if not file.endswith(".cpp") or file.endswith(OUTPUT_SUFFIX):
                continue

            total_cpp_files += 1
            cpp_path = os.path.join(root, file)
            slug = os.path.basename(file).replace(".cpp", "")
            output_path = os.path.join(root, slug + OUTPUT_SUFFIX)

            # Skip if benchmark already exists
            if os.path.exists(output_path):
                print(f"Skipping existing benchmark for: {slug}")
                skipped_existing += 1
                continue

            print(f"\n Generating benchmark for: {slug}")

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
