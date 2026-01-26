import subprocess
import csv
from pathlib import Path
from collections import defaultdict



ROOT = Path("newv2_cleaned_new_transpiled_solutions copy 2")
OUTPUT_CSV = Path("CHECK_SUM_CLEANED_BEFORE_CUMULATIVE.csv")

#checksum_comparison_before_v3.csv


def compile_cpp(source_path: Path, build_dir: Path) -> Path:
    build_dir.mkdir(parents=True, exist_ok=True)
    exe_path = build_dir / source_path.stem
    subprocess.run(
        ["g++", "-O2", str(source_path), "-o", str(exe_path)],
        check=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    return exe_path

def run_and_capture(cmd):
    """
    Runs a command and returns stripped stdout.
    """
    out = subprocess.check_output(cmd, stderr=subprocess.STDOUT)
    return out.decode("utf-8", errors="ignore").strip()



def main():
    cpp_files = ROOT.glob("**/*_benchmark_v2.cpp")
    py_files  = ROOT.glob("**/*_benchmark_v2.py")

    problems = defaultdict(dict)

    for f in cpp_files:
        problem = f.parts[-3] if len(f.parts) >= 3 else f.stem
        problems[problem]["cpp"] = f

    for f in py_files:
        problem = f.parts[-3] if len(f.parts) >= 3 else f.stem
        problems[problem]["python2"] = f

    rows = []

    for problem, langs in sorted(problems.items()):
        row = {
            "problem": problem,
            "cpp_checksum": None,
            "python2_checksum": None,
            "match": None,
            "error": "",
        }

       
        if "cpp" in langs:
            try:
                exe = compile_cpp(langs["cpp"], langs["cpp"].parent / "build")
                row["cpp_checksum"] = run_and_capture([str(exe)])
            except Exception as e:
                row["error"] += f"C++ failed: {e}; "

 
        if "python2" in langs:
            try:
                row["python2_checksum"] = run_and_capture(
                    ["python2", str(langs["python2"])]
                )
            except Exception as e:
                row["error"] += f"Python2 failed: {e}; "

        if row["cpp_checksum"] is not None and row["python2_checksum"] is not None:
            row["match"] = row["cpp_checksum"] == row["python2_checksum"]

        rows.append(row)


    with open(OUTPUT_CSV, "w", newline="") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=[
                "problem",
                "cpp_checksum",
                "python2_checksum",
                "match",
                "error",
            ],
        )
        writer.writeheader()
        writer.writerows(rows)

    print(f"Checksum comparison saved to {OUTPUT_CSV}")

# ===================== ENTRY =====================

if __name__ == "__main__":
    main()
