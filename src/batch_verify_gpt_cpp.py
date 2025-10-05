#!/usr/bin/env python3
"""
Batch verify GPT-generated C++ solutions in kamyu_hard_mirror against LeetCode.

This script walks through all cpp_gpt subdirectories in the mirror, submits each
C++ file to LeetCode for verification, and tracks the results in a CSV.
"""

import argparse
import csv
import json
import sys
import time
from pathlib import Path
from typing import List, Optional


def find_gpt_cpp_files(mirror_root: Path) -> List[tuple[str, Path, Path]]:
    """Find all GPT-generated C++ files in the mirror.
    
    Returns:
        List of (slug, cpp_file_path, meta_file_path) tuples
    """
    results = []
    
    for problem_dir in sorted(mirror_root.iterdir()):
        if not problem_dir.is_dir():
            continue
            
        # Look for cpp_gpt subdirectory
        cpp_gpt_dir = problem_dir / "cpp_gpt"
        if not cpp_gpt_dir.exists():
            continue
            
        # Extract slug from directory name
        slug = problem_dir.name
        if "__" in slug:
            slug = slug.split("__", 1)[1]
            
        # Find C++ files
        for cpp_file in cpp_gpt_dir.glob("*.cpp"):
            meta_file = cpp_file.with_suffix(cpp_file.suffix + ".meta.json")
            results.append((slug, cpp_file, meta_file))
            
    return results


def load_metadata(meta_file: Path) -> dict:
    """Load metadata from .meta.json file."""
    if not meta_file.exists():
        return {}
    try:
        return json.loads(meta_file.read_text(encoding="utf-8"))
    except Exception:
        return {}


def run_verify_single(slug: str, cpp_file: Path, cookies_file: Path) -> dict:
    """Run verification for a single C++ file."""
    import subprocess
    import sys
    
    try:
        # Run the verify script as a subprocess
        cmd = [
            sys.executable, "src/verify_on_leetcode.py",
            "--slug", slug,
            "--lang", "cpp", 
            "--code-file", str(cpp_file),
            "--cookies", str(cookies_file)
        ]
        
        result = subprocess.run(cmd, capture_output=True, text=True, timeout=120)
        
        if result.returncode == 0:
            # Parse the output for result information
            output = result.stdout
            if "Accepted" in output:
                # Extract runtime and memory if available
                runtime = ""
                memory = ""
                submission_id = ""
                
                lines = output.split('\n')
                for line in lines:
                    if "Runtime:" in line:
                        runtime = line.split("Runtime:")[1].strip()
                    elif "Memory:" in line:
                        memory = line.split("Memory:")[1].strip()
                    elif "submission_id" in line.lower():
                        # Try to extract submission ID
                        parts = line.split()
                        for part in parts:
                            if part.isdigit() and len(part) > 5:
                                submission_id = part
                                break
                
                return {
                    "status": "pass",
                    "runtime": runtime,
                    "memory": memory,
                    "error": "",
                    "submission_id": submission_id
                }
            else:
                return {
                    "status": "fail", 
                    "runtime": "",
                    "memory": "",
                    "error": output.strip(),
                    "submission_id": ""
                }
        else:
            return {
                "status": "error",
                "runtime": "",
                "memory": "", 
                "error": result.stderr.strip() or result.stdout.strip(),
                "submission_id": ""
            }
            
    except subprocess.TimeoutExpired:
        return {
            "status": "error",
            "runtime": "",
            "memory": "",
            "error": "Verification timeout",
            "submission_id": ""
        }
    except Exception as e:
        return {
            "status": "error",
            "runtime": "",
            "memory": "",
            "error": str(e),
            "submission_id": ""
        }


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", default="kamyu_hard_mirror", 
                       help="Mirror root directory to scan")
    parser.add_argument("--cookies", required=True,
                       help="Path to LeetCode cookies JSON file")
    parser.add_argument("--out-csv", default="data/test_passing_solution_generated_by_GPT.csv",
                       help="Output CSV file for results")
    parser.add_argument("--sleep", type=float, default=15.0,
                       help="Seconds to sleep between submissions")
    parser.add_argument("--limit", type=int, default=0,
                       help="Limit number of files to test (0 = no limit)")
    parser.add_argument("--slug", action="append",
                       help="Test only specific slug(s)")
    parser.add_argument("--dry-run", action="store_true",
                       help="List files without submitting")
    
    args = parser.parse_args()
    
    mirror_root = Path(args.root).resolve()
    if not mirror_root.exists():
        print(f"Error: Mirror root not found: {mirror_root}")
        return 1
        
    cookies_file = Path(args.cookies).resolve()
    if not cookies_file.exists():
        print(f"Error: Cookies file not found: {cookies_file}")
        return 1
    
    # Find all GPT-generated C++ files
    print("Scanning for GPT-generated C++ files...")
    cpp_files = find_gpt_cpp_files(mirror_root)
    
    # Filter by slug if specified
    if args.slug:
        target_slugs = set()
        for slug_arg in args.slug:
            target_slugs.update(s.strip() for s in slug_arg.split(",") if s.strip())
        cpp_files = [(slug, cpp_path, meta_path) for slug, cpp_path, meta_path in cpp_files 
                     if slug in target_slugs]
    
    print(f"Found {len(cpp_files)} GPT-generated C++ files to verify")
    
    if not cpp_files:
        print("No files to verify")
        return 0
    
    # Prepare output CSV
    out_csv_path = Path(args.out_csv)
    out_csv_path.parent.mkdir(parents=True, exist_ok=True)
    
    # CSV headers
    headers = [
        "slug", "cpp_file", "model", "generation_timestamp", 
        "verification_status", "runtime", "memory", "error_message", 
        "submission_id", "verification_timestamp"
    ]
    
    if args.dry_run:
        print("DRY RUN - Would verify these files:")
        for slug, cpp_file, meta_file in cpp_files[:args.limit] if args.limit else cpp_files:
            print(f"  {slug}: {cpp_file}")
        return 0
    
    # Start verification process
    processed = 0
    passed = 0
    failed = 0
    errors = 0
    
    with open(out_csv_path, "w", newline="", encoding="utf-8") as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(headers)
        
        for slug, cpp_file, meta_file in cpp_files:
            if args.limit and processed >= args.limit:
                break
                
            print(f"\n[{processed + 1}/{len(cpp_files)}] Verifying {slug}...")
            
            # Load metadata
            metadata = load_metadata(meta_file)
            model = metadata.get("model", "unknown")
            gen_timestamp = metadata.get("timestamp_utc", "")
            
            # Run verification
            result = run_verify_single(slug, cpp_file, cookies_file)
            verification_timestamp = time.strftime("%Y-%m-%dT%H:%M:%SZ")
            
            # Update counters
            if result["status"] == "pass":
                passed += 1
                print(f"  ✅ PASSED - Runtime: {result['runtime']}, Memory: {result['memory']}")
            elif result["status"] == "fail":
                failed += 1
                print(f"  ❌ FAILED - {result['error']}")
            else:
                errors += 1
                print(f"  🔥 ERROR - {result['error']}")
            
            # Write to CSV
            writer.writerow([
                slug,
                cpp_file.as_posix(),
                model,
                gen_timestamp,
                result["status"],
                result["runtime"],
                result["memory"],
                result["error"],
                result["submission_id"],
                verification_timestamp
            ])
            
            # Flush CSV after each write
            csvfile.flush()
            
            processed += 1
            
            # Sleep between requests
            if processed < len(cpp_files) and args.sleep > 0:
                print(f"  Sleeping {args.sleep}s...")
                time.sleep(args.sleep)
    
    # Final statistics
    print(f"\n=== VERIFICATION COMPLETE ===")
    print(f"Total processed: {processed}")
    print(f"Passed: {passed} ({passed/processed*100:.1f}%)")
    print(f"Failed: {failed} ({failed/processed*100:.1f}%)")
    print(f"Errors: {errors} ({errors/processed*100:.1f}%)")
    print(f"Results saved to: {out_csv_path}")
    
    return 0


if __name__ == "__main__":
    sys.exit(main())