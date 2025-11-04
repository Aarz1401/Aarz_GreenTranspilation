# Aarz Green Transpilation

Quantifying energy efficiency differences between Python and C++ implementations through automated benchmarking on LeetCode hard problems.

## Overview

This project provides an end-to-end workflow for:
1. Fetching LeetCode problems (before/after GPT-4 cutoff: Sept 30, 2024)
2. Verifying Python solutions on LeetCode
3. Translating Python → C++ using GPT-4
4. Verifying C++ solutions on LeetCode
5. Measuring energy consumption with macOS powermetrics
6. Analyzing energy efficiency differences

**Key Result**: C++ uses **42.9x less energy** than Python (median across benchmarked programs)

## Quick Start

### Prerequisites

```bash
# Python 3.9+ with virtual environment
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt

# Python 2.7 for benchmarks (if needed)
# Install via pyenv: pyenv install 2.7.18
# Install sortedcontainers: pip install sortedcontainers

# macOS powermetrics (built-in, requires sudo)
# Stats.app for temperature monitoring (optional but recommended)
```

### View Existing Results

```bash
# Check CSV files for benchmark results
cat csv/energy_results_combined_v3.csv
cat csv/batch_verify_results_cpp.csv
cat csv/batch_verify_results_py2_v2.csv
```

## Project Structure

```
Aarz_GreenTranspilation/
├── src/                            # Python scripts
│   ├── batch_verify_cpp.py        # Verify C++ solutions on LeetCode
│   ├── batch_verify_on_leetcode.py # Verify Python solutions
│   ├── build_database.py          # Database utilities
│   ├── combo_after_energy.py      # Energy analysis (after cutoff)
│   ├── combo_energy_v2.py         # Energy analysis v2
│   ├── crossref_from_csv.py       # Cross-reference solutions
│   ├── get_python_ans.py          # Extract Python answers
│   ├── getting_test_cases.py      # Fetch LeetCode test cases
│   ├── pull_whiskwhite_problems.py # Scrape LeetCode problems
│   └── verify_on_leetcode.py      # LeetCode verification
├── csv/                            # Data and results (CSV files)
│   ├── accepted_v2.csv            # Accepted solutions
│   ├── batch_verify_cpp_v1.csv    # C++ verification results v1
│   ├── batch_verify_results_cpp.csv # C++ verification results
│   ├── batch_verify_results_py2_v2.csv # Python2 verification results
│   ├── crossref_kamyu_v1.csv      # Kamyu solution cross-reference
│   ├── energy_results_combined_v3.csv # Energy benchmark results
│   ├── fin_energy_after.csv       # Final energy (after cutoff)
│   ├── fin_energy_before_v2.csv   # Final energy (before cutoff)
│   ├── passed_python2_after.csv   # Passing Python2 solutions
│   └── whisk_problems_v_fin.csv   # Scraped problem database
├── transpiled_before/              # Problems before Sept 30, 2024 cutoff (120 problems)
│   └── [slug]/                    # Each problem by slug (e.g., 123__best-time-to-buy-and-sell-stock-iii)
│       └── cpp/                   # Contains .cpp, .py, and benchmark files
├── transpiled_after/               # Problems after Sept 30, 2024 cutoff (41 feasible problems)
│   └── [slug]/                    # Each problem by slug (e.g., check-if-dfs-strings-are-palindromes)
│       └── cpp/                   # Contains .cpp, .py, and benchmark files
├── jupyter/                        # Jupyter notebooks for analysis (21 notebooks)
├── energy expenditure.png          # Energy consumption visualization
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

### 4. Verify C++ Solutions on LeetCode

```bash
python src/batch_verify_cpp.py \
  --root solutions_dir \
  --cookies leetcode_cookies.json \
  --out-csv csv/verify_results_cpp.csv \
  --sleep 15
```

### 5. Run Energy Benchmarks

```bash
# Requires sudo for powermetrics
sudo bash run_benchmarks.sh

# Results saved to csv/energy_results_combined.csv
```

## Energy Benchmarking Framework

### Methodology

- **Tool**: macOS powermetrics (50ms sampling interval)
- **Runs**: Multiple runs per language per benchmark
- **Temperature Monitoring**: Stats.app smc tool for thermal control
- **Thermal Control**: Automatic cooling pauses if temperature rises significantly
- **Iteration Constraints**:
  - C++ must run ≥0.5s (reliable powermetrics sampling)
  - Python must run ≤50s (avoid OOM errors)
  - Both languages use identical iterations per benchmark

### Results Format

CSV output includes:
- `problem`: Benchmark name
- `cpp_power_mw`, `cpp_time_s`, `cpp_energy_j`: C++ metrics
- `py_power_mw`, `py_time_s`, `py_energy_j`: Python metrics
- `power_ratio`, `time_ratio`, `energy_ratio`: Python/C++ ratios
- `cpp_temp_c`, `py_temp_c`: Average CPU temperature (°C)

## Key Datasets

### CSV Files

- **[whisk_problems_v_fin.csv](csv/whisk_problems_v_fin.csv)**: Complete database of scraped LeetCode problems
- **[batch_verify_results_cpp.csv](csv/batch_verify_results_cpp.csv)**: C++ verification results
- **[batch_verify_results_py2_v2.csv](csv/batch_verify_results_py2_v2.csv)**: Python2 verification results
- **[energy_results_combined_v3.csv](csv/energy_results_combined_v3.csv)**: Energy benchmark results
- **[crossref_kamyu_v1.csv](csv/crossref_kamyu_v1.csv)**: Cross-reference with Kamyu's solutions
- **[accepted_v2.csv](csv/accepted_v2.csv)**: Accepted solutions list

## Troubleshooting

### Powermetrics shows 0 J energy

**Cause**: Program runs too fast (< 0.5s), powermetrics can't sample enough

**Solution**: Increase iteration count in benchmark files

### Python benchmark crashes (OOM)

**Cause**: Python runs too long or uses too much memory

**Solution**: Reduce iterations or exclude from benchmark set

### Temperature warnings

**Cause**: CPU temperature rises during benchmarking

**Solution**:
- Ensure good ventilation
- Close other applications
- Use built-in cooling pauses in scripts
- Install Stats.app for temperature monitoring

## Visualization

See [energy expenditure.png](energy%20expenditure.png) for energy consumption visualization comparing Python and C++ implementations.

## Requirements

```
selenium
requests
beautifulsoup4
pandas
numpy
matplotlib
```

## License

MIT License

## Acknowledgments

- [Kamyu's LeetCode Solutions](https://github.com/kamyu104/LeetCode-Solutions) - Python solution source
- [LeetCode](https://leetcode.com) - Problem platform
- OpenAI GPT-4 - Python → C++ translation assistance
