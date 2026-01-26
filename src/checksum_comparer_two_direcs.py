import subprocess
import csv
from pathlib import Path


PY_ROOT  = Path("newv2_matched_kamyu_after")
CPP_ROOT = Path("newv2_CPP_CLEANED_AFTER")
OUT_CSV  = Path("ERROR_CHECK_AFTER_v2.csv")
#CHECK_SUM_AFTER_CUMULATIVE_v1.csv
PY_SUFFIX  = "_benchmark_v2.py"
CPP_SUFFIX = "_benchmark_v2.cpp"


#Helpers: 
def run_python2(script: Path) -> int:
    out = subprocess.check_output(
        ["python2", str(script)],
        stderr=subprocess.STDOUT,
        text=True
    )
    return int(out.strip())

def run_cpp(source: Path) -> int:
    exe = source.with_suffix("")  # output binary in same folder
    subprocess.run(
        ["g++", "-O2", str(source), "-o", str(exe)],
        check=True
    )
    out = subprocess.check_output(
        [str(exe)],
        stderr=subprocess.STDOUT,
        text=True
    )
    return int(out.strip())
    # return None

def collect(root: Path, suffix: str):
    """
    Recursively collect all files ending with `suffix`.
    Returns a dict mapping problem folder name -> file path.
    """
    table = {}
    for f in root.rglob(f"*{suffix}"):
        problem = f.parent.name
        table[problem] = f
    return table

#Main 

def main():
    # collect files ending with proper suffixes
    py_files  = collect(PY_ROOT, PY_SUFFIX)
    cpp_files = collect(CPP_ROOT, CPP_SUFFIX)

    # merge all problem names
    problems = sorted(set(py_files) | set(cpp_files))
    rows = []

    for problem in problems:
        row = {
            "problem": problem,
            "cpp_checksum": None,
            "python2_checksum": None,
            "match": None,
            "error": ""
        }

        try:
            # run C++ benchmark if present
            if problem in cpp_files:
                row["cpp_checksum"] = run_cpp(cpp_files[problem])

            # run Python2 benchmark if present
            if problem in py_files:
                row["python2_checksum"] = run_python2(py_files[problem])

            # compare checksums if both exist
            if row["cpp_checksum"] is not None and row["python2_checksum"] is not None:
                row["match"] = row["cpp_checksum"] == row["python2_checksum"]

        except Exception as e:
            row["error"] = str(e)

        rows.append(row)

    # write CSV
    with open(OUT_CSV, "w", newline="") as f:
        writer = csv.DictWriter(
            f,
            fieldnames=["problem", "cpp_checksum", "python2_checksum", "match", "error"]
        )
        writer.writeheader()
        writer.writerows(rows)

    print(f"Wrote {OUT_CSV}")

if __name__ == "__main__":
    main()
