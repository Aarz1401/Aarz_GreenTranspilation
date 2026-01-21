int main() {
    // Prepare 10 diverse test inputs
    vector<pair<string, int>> tests;
    tests.emplace_back("", 0);                              // Empty string, k = 0
    tests.emplace_back("a", 1);                             // Single character, k = runs
    tests.emplace_back("aaaaaa", 3);                        // Single run, k > runs
    tests.emplace_back("ababababab", 5);                    // Alternating chars, k < runs
    tests.emplace_back("aaabbbcccddd", 4);                  // Multiple equal runs, k = runs
    tests.emplace_back("zzzzzyxxxx", 7);                    // Mixed runs, k > runs
    tests.emplace_back("a1a1a1bbbccddeeee", 12);            // Alphanumeric with varied runs, moderate k
    tests.emplace_back("abcdef", 3);                        // All unique, k < runs
    {
        string base = "abcdefghijklmnopqrstuvwxyz";
        string longPattern;
        for (int i = 0; i < 20; ++i) longPattern += base;   // 520 chars, all runs of length 1
        tests.emplace_back(longPattern, 100);               // k < runs to avoid DP branch
    }
    tests.emplace_back(string(300, 'b') + string(200, 'c'), 50); // Two long runs, k > runs but m < run lengths

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            checksum += static_cast<uint64_t>(sol.possibleStringCount(tc.first, tc.second));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed << "\n";

    return 0;
}