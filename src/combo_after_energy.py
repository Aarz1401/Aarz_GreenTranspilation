import pyRAPL
import subprocess
import time
import csv
import psutil
import statistics
import multiprocessing, math
from pathlib import Path

# setup
ROOT = Path("new_transpiled_solutions")
OUTPUT_CSV = Path("energy_after_combined.csv")

COOL_TEMP_C = 44.0
CHECK_INTERVAL = 2
REPEAT_RUNS = 10  # Number of times each benchmark is run to average

pyRAPL.setup()


def compile_cpp(source_path: Path, build_dir: Path) -> Path:
    """Compile C++ source into an executable."""
    build_dir.mkdir(exist_ok=True, parents=True)
    exe_path = build_dir / (source_path.stem + "_run")
    compile_cmd = ["g++", "-O2", "-std=c++17", str(source_path), "-o", str(exe_path)]
    print(f"Compiling {source_path}...")
    subprocess.run(compile_cmd, check=True)
    return exe_path


def safe_energy_value(value):
    """Handle pyRAPL energy readings (convert to joules if in microjoules)."""
    try:
        if isinstance(value, list):
            v = value[0]
            val = v.energy if hasattr(v, "energy") else float(v)
        elif hasattr(value, "energy"):
            val = value.energy
        elif isinstance(value, (float, int)):
            val = float(value)
        else:
            return None

        if val > 1e3:
            val /= 1e6
        return val
    except Exception:
        return None

def cpu_warmup(duration=5):
    """Spin all cores for `duration` seconds to warm CPU."""
    def burn(t):
        end = time.time() + t
        while time.time() < end:
            math.sqrt(12345.6789)

    procs = []
    for _ in range(multiprocessing.cpu_count()):
        p = multiprocessing.Process(target=burn, args=(duration,))
        p.start()
        procs.append(p)
    for p in procs:
        p.join()

def get_avg_cpu_temp():
    """Return the average CPU temperature in Celsius."""
    temps = psutil.sensors_temperatures()
    if not temps:
        return None
    if "coretemp" in temps:
        readings = [t.current for t in temps["coretemp"] if t.current is not None]
    else:
        first = next(iter(temps.values()))
        readings = [t.current for t in first if t.current is not None]
    return sum(readings) / len(readings) if readings else None



def run_cpp_with_energy(exe_path: Path, min_temp=43.0, max_temp=45.0, interval=2):
    """Run a compiled C++ benchmark."""
    print(f"Adjusting CPU to {min_temp:.1f}–{max_temp:.1f}°C before measurement")

    while True:
        temp = get_avg_cpu_temp()
        if temp is None:
            print("Could not read CPU temperature")
            break

        if temp > max_temp:
            print(f"Temp {temp:.1f}°C > {max_temp:.1f}°C, cooling")
            time.sleep(interval)
            continue

        if temp < min_temp:
            print(f"Temp {temp:.1f}°C < {min_temp:.1f}°C, warming up")
            # Warm-up run (not measured)
            cpu_warmup(duration=2)
            time.sleep(1)
            continue

        print(f"CPU stabilized at {temp:.1f}°C, starting energy measurement.\n")
        break

    _ = pyRAPL.Measurement(exe_path.stem + "_warmup")

    meter = pyRAPL.Measurement(exe_path.stem)
    start_temp = get_avg_cpu_temp()
    start_time = time.time()
    meter.begin()
    try:
        subprocess.run([str(exe_path)], check=True)
    finally:
        meter.end()
    end_time = time.time()
    end_temp = get_avg_cpu_temp()

    pkg_energy = safe_energy_value(meter.result.pkg)
    dram_energy = safe_energy_value(meter.result.dram)

    return end_time - start_time, pkg_energy, dram_energy, start_temp, end_temp



def run_python2_with_energy(script_path: Path, min_temp=43.0, max_temp=45.0, interval=2):
    """Run Python2 benchmark"""
    print(f"Adjusting CPU to {min_temp:.1f}–{max_temp:.1f}°C ")

    while True:
        temp = get_avg_cpu_temp()
        if temp is None:
            print("Could not read CPU temperature")
            break

        if temp > max_temp:
            print(f"Temp {temp:.1f}°C > {max_temp:.1f}°C, cooling")
            time.sleep(interval)
            continue

        if temp < min_temp:
            print(f"Temp {temp:.1f}°C < {min_temp:.1f}°C, warming up")
            # Warm-up run (not measured)
            cpu_warmup(duration=2)
            time.sleep(1)
            continue

        print(f"CPU stabilized at {temp:.1f}°C, starting energy measurement.\n")
        break

    _ = pyRAPL.Measurement(script_path.stem + "_warmup")

    meter = pyRAPL.Measurement(script_path.stem)
    start_temp = get_avg_cpu_temp()
    start_time = time.time()
    meter.begin()
    try:
        subprocess.run(["python2", str(script_path)], check=True)
    finally:
        meter.end()
    end_time = time.time()
    end_temp = get_avg_cpu_temp()

    pkg_energy = safe_energy_value(meter.result.pkg)
    dram_energy = safe_energy_value(meter.result.dram)

    return end_time - start_time, pkg_energy, dram_energy, start_temp, end_temp


def main():
    results = []
    cpp_root = Path("cpp_energy_test_final_feasible")
    py_root = Path("py2_energy_test_final_feasible")

    cpp_files = sorted(cpp_root.glob("**/*_benchmark.cpp"))
    py_files = sorted(py_root.glob("**/*_benchmark.py"))
    print(f"Found {len(cpp_files)} C++ and {len(py_files)} Python2 benchmark files.\n")

    max_len = max(len(cpp_files), len(py_files))
    for i in range(max_len):
        for lang, file_list in (("cpp", cpp_files), ("python2", py_files)):
            if i >= len(file_list):
                continue

            file_path = file_list[i]
            problem_name = file_path.parts[-3] if len(file_path.parts) >= 3 else file_path.stem

            try:
                if lang == "cpp":
                    print(f"Running C++ benchmark for {problem_name} (10×)...")
                    exe_path = compile_cpp(file_path, file_path.parent / "build")

                    durations, pkgs, drams = [], [], []
                    for _ in range(REPEAT_RUNS):
                        duration, pkg, dram, _, _ = run_cpp_with_energy(exe_path)
                        durations.append(duration)
                        pkgs.append(pkg)
                        drams.append(dram)

                else:
                    print(f"Running Python2 benchmark for {problem_name} (10×)...")
                    durations, pkgs, drams = [], [], []
                    for _ in range(REPEAT_RUNS):
                        duration, pkg, dram, _, _ = run_python2_with_energy(file_path)
                        durations.append(duration)
                        pkgs.append(pkg)
                        drams.append(dram)

                avg_duration = statistics.mean(durations)
                avg_pkg = statistics.mean([v for v in pkgs if v is not None])
                avg_dram = statistics.mean([v for v in drams if v is not None])

                print(f" {problem_name} ({lang}): {avg_duration:.3f}s, pkg={avg_pkg:.6f}J, dram={avg_dram:.6f}J\n")

                results.append({
                    "problem": problem_name,
                    "language": lang,
                    "path": str(file_path),
                    "avg_duration_sec": avg_duration,
                    "avg_pkg_joules": avg_pkg,
                    "avg_dram_joules": avg_dram,
                    "error": ""
                })

            except subprocess.CalledProcessError as e:
                print(f"Failed for {file_path}: {e}")
                results.append({
                    "problem": problem_name,
                    "language": lang,
                    "path": str(file_path),
                    "avg_duration_sec": None,
                    "avg_pkg_joules": None,
                    "avg_dram_joules": None,
                    "error": str(e)
                })

    print("Writing results to CSV...")
    with open(OUTPUT_CSV, "w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=[
            "problem", "language", "path",
            "avg_duration_sec", "avg_pkg_joules", "avg_dram_joules", "error"
        ])
        writer.writeheader()
        writer.writerows(results)

    print(f"Results saved to {OUTPUT_CSV}")


if __name__ == "__main__":
    main()
