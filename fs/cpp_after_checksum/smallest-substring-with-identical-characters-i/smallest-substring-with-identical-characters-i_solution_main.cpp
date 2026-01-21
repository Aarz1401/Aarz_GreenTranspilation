int main() {
    // Generate 10 diverse test inputs (string s, int numOps)
    vector<pair<string, int>> tests;
    tests.reserve(10);

    // 1) Single zero, zero ops
    tests.emplace_back(string("0"), 0);

    // 2) Single one, one op
    tests.emplace_back(string("1"), 1);

    // 3) Alternating even length, zero ops
    tests.emplace_back(makeAlternating(10, '0'), 0);

    // 4) Small mixed blocks, small ops
    tests.emplace_back(string("00110011"), 1);

    // 5) All zeros, moderate ops
    tests.emplace_back(string(100, '0'), 10);

    // 6) All ones, zero ops, odd length
    tests.emplace_back(string(257, '1'), 0);

    // 7) Random length 1000, arbitrary ops
    tests.emplace_back(makeRandom01(1000, 42u), 123);

    // 8) Long runs with varied sizes
    tests.emplace_back(
        makeRuns({
            {'0', 10}, {'1', 10}, {'0', 8}, {'1', 6}, {'0', 1}, {'1', 20}, {'0', 5}
        }),
        5
    );

    // 9) Mixed pattern with increasing/decreasing run lengths
    tests.emplace_back(
        makeRuns({
            {'0', 3}, {'1', 3}, {'0', 2}, {'1', 4}, {'0', 4}, {'1', 5}, {'0', 6}, {'1', 2}
        }),
        8
    );

    // 10) Larger random length 5000, higher ops
    tests.emplace_back(makeRandom01(5000, 2025u), 777);

    Solution sol;

    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.minLength(tests[i].first, tests[i].second);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}