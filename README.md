# Aarz Green Transpilation

Quantifying energy efficiency differences between Python and C++ implementations through automated benchmarking on LeetCode hard problems.

## Overview

This project provides an end-to-end workflow for:
1. Fetching LeetCode problems (before/after GPT-5 cutoff: Sept 30, 2024)
2. Verifying Python solutions on LeetCode
3. Translating Python → C++ using GPT-5
4. Verifying C++ solutions on LeetCode
5. Adding test cases to C++ code 
6. Translating test cases to python code
7. Measuring energy consumption with pyRAPL
8. Analyzing energy efficiency differences


## Quick Start

### Prerequisites

```bash
# Python 3.9+ with virtual environment
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt

# Python 2.7 for benchmarks 
# Install via pyenv: pyenv install 2.7.18
```

### View Existing Results

```bash
# Check CSV files for benchmark results
cat csv/FILTERED_BEFOR_CHECKSUM_ENERGY_READING_FULL_V1.csv
cat csv/FILTERED_AFTER_CHECKSUM_ENERGY_READING_FULL_V1.csv
cat csv/batch_verify_results_py2_v2.csv

# Check CSV files for checksum results
cat csv/CHECK_SUM_AFTER_CUMULATIVE_v1.csv
cat csv/CHECK_SUM_CLEANED_BEFORE_CUMULATIVE.csv
```

## Project Structure

```
Aarz_GreenTranspilation/
├── src/                            # Python scripts
│   ├── batch_verify_cpp.py        # Verify C++ solutions on LeetCode
│   ├── batch_verify_on_leetcode.py # Verify Python solutions
│   ├── build_database.py          # Database utilities
│   ├── combo_after_energy.py      # Energy analysis for py directory and cpp directory
│   ├── combo_energy_v2.py         # Energy analysis for py and cpp in same directory
|   ├── checksum_comparer_two_direcs.py # Energy analysis for py directory and cpp directory
|   ├── checksum_comparer.py       # checksum for py and cpp in same directory 
│   ├── crossref_from_csv.py       # Cross-reference solutions
│   ├── get_python_ans.py          # Translating Cpp test cases to python
│   ├── getting_test_cases.py      # Generating Cpp test cases 
│   ├── fs\v2_get_python_solutions.py # Translates from Python to C++
│   ├── pull_whiskwhite_problems.py # Scrape LeetCode problems
│   └── verify_on_leetcode.py      # LeetCode verification
├── csv/                            # Data and results (CSV files)
│   ├── accepted_v2.csv            # Accepted solutions
│   ├── batch_verify_cpp_v1.csv    # C++ verification results v1
│   ├── batch_verify_results_cpp.csv # C++ verification results
│   ├── batch_verify_results_py2_v2.csv # Python2 verification results
│   ├── crossref_kamyu_v1.csv      # Kamyu solution cross-reference
│   ├── FILTERED_AFTER_CHECKSUM_ENERGY_READING_FULL_V1.csv  # Final energy (after cutoff)
│   ├── FILTERED_BEFOR_CHECKSUM_ENERGY_READING_FULL_V1.csv   # Final energy (before cutoff)
│   ├── passed_python2_after.csv   # Passing Python2 solutions
│   └── whisk_problems_v_fin.csv   # Scraped problem database
├── cpp_before_energy & py_before_energy/  # Problems before Sept 30, 2024 cutoff 
│   └── [slug]/                    # Each problem by slug (e.g., 123__best-time-to-buy-and-sell-stock-iii), Contains .cpp, .py, and test case files
├── cpp_after_energy & py_after_energy/  # Problems after Sept 30, 2024 cutoff 
│   └── [slug]/                    # Each problem by slug (e.g., check-if-dfs-strings-are-palindromes), Contains .cpp, .py, and benchmark files
├── cpp_before_checksum & py_before_checksum/
│   └── [slug]/                     # Each problem by slug (e.g., check-if-dfs-strings-are-palindromes), Contains .cpp, .py, and benchmark files
├── cpp_before_checksum & py_before_checksum/
│   └── [slug]/                     # Each problem by slug (e.g., check-if-dfs-strings-are-palindromes), Contains .cpp, .py, and benchmark files
├── jupyter/                        # Jupyter notebooks for analysis (21 notebooks)
└── README.md                       # This file
```

## Workflow

### 1. Fetch LeetCode Problems

```bash
# Fetch problems after a specific date
python src/pull_whiskwhite_problems.py \
  --date-after 2024-09-30 \
  --out-csv csv/scraped_problems.csv \
  --out-dir problems_after_cutoff

# Fetch problems before a specific date
python src/pull_whiskwhite_problems.py \
  --date-before 2024-09-30 \
  --out-csv csv/scraped_problems_before.csv \
  --out-dir problems_before_cutoff
```

### 2. Cross-reference with Kamyu Solutions

```bash
python src/crossref_from_csv.py \
  --kamyu-dir "/path/to/LeetCode-Solutions" \
  --in-csv csv/scraped_problems.csv \
  --out-csv csv/crossref_kamyu.csv \
  --out-db crossref_kamyu.db \
  --mirror-dir kamyu_mirror
```

### 3. Verify Python Solutions on LeetCode

```bash
python src/batch_verify_on_leetcode.py \
  --root kamyu_mirror \
  --cookies leetcode_cookies.json \
  --out-csv csv/verify_results_python.csv \
  --sleep 12 --max-retries 4
```

### 4. Generate C++ Solutions 

```bash
  python v2_get_python_solutions.py
```



### 5. Verify C++ Solutions on LeetCode

```bash
python src/batch_verify_cpp.py \
  --root solutions_dir \
  --cookies leetcode_cookies.json \
  --out-csv csv/verify_results_cpp.csv \
  --sleep 15
```
### 6. Generate C++ test cases 

```bash
  python getting_test_cases.py
```

### 7. Translate test cases from C++ to Python2  

```bash
  python get_python_ans.py
```

### 8. Run Checksum Comparison

```bash
  python checksum_comparer_two_direcs.py
```

### 9. Run Energy Benchmarks

```bash
  python combo_after_energy.py 
```


## Energy Benchmarking Framework

### Methodology

- **Tool**: pyRAPL 
- **Runs**: Multiple runs per language per benchmark
- **Thermal Control**: Automatic cooling pauses if temperature rises significantly

## Key Datasets

### CSV Files

- **[whisk_problems_v_fin.csv](csv/whisk_problems_v_fin.csv)**: Complete database of scraped LeetCode problems
- **[batch_verify_results_cpp.csv](csv/batch_verify_results_cpp.csv)**: C++ verification results
- **[batch_verify_results_py2_v2.csv](csv/batch_verify_results_py2_v2.csv)**: Python2 verification results
- **[FILTERED_AFTER_CHECKSUM_ENERGY_READING_FULL_V1.csv](csv/FILTERED_AFTER_CHECKSUM_ENERGY_READING_FULL_V1.csv)**: Energy benchmark results
- **[FILTERED_BEFOR_CHECKSUM_ENERGY_READING_FULL_V1.csv](csv/FILTERED_BEFOR_CHECKSUM_ENERGY_READING_FULL_V1.csv)**: Energy benchmark results
- **[crossref_kamyu_v1.csv](csv/crossref_kamyu_v1.csv)**: Cross-reference with Kamyu's solutions
- **[accepted_v2.csv](csv/accepted_v2.csv)**: Accepted solutions list

## License

MIT License

## Acknowledgments

- [Kamyu's LeetCode Solutions](https://github.com/kamyu104/LeetCode-Solutions) - Python solution source
- [LeetCode](https://leetcode.com) - Problem platform
- OpenAI GPT-5 - Python → C++ translation assistance

