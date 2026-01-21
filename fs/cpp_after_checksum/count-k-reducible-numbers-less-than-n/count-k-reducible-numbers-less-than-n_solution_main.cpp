int main() {
    // Generate 10 diverse test inputs (string s, int k)
    vector<pair<string, int>> tests;
    tests.emplace_back(string(""), 0);                               // 1) empty string
    tests.emplace_back(string("0"), 1);                              // 2) single zero
    tests.emplace_back(string("1"), 1);                              // 3) single one
    tests.emplace_back(makeAlternating(10), 2);                      // 4) alternating length 10
    tests.emplace_back(makeAll(32, '1'), 3);                         // 5) all ones length 32
    tests.emplace_back(makeAll(64, '0'), 4);                         // 6) all zeros length 64
    tests.emplace_back(makePattern100(75), 2);                       // 7) "1" every 3rd position length 75
    tests.emplace_back(makeAlternating(128), 5);                     // 8) alternating length 128
    tests.emplace_back(makePrimeOnes(200), 4);                       // 9) ones at prime indices length 200
    tests.emplace_back(makeDeterministicPseudo(256), 6);             // 10) deterministic pseudo-random length 256

    Solution sol;

    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            checksum += sol.countKReducibleNumbers(tc.first, tc.second);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = elapsed_ns / 1e6;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}