int main() {
    // Prepare 10 diverse test cases
    vector<vector<int>> testCases;
    testCases.reserve(10);

    // 1) Empty array
    vector<int> tc1;
    testCases.push_back(tc1);

    // 2) Single element
    vector<int> tc2 = {42};
    testCases.push_back(tc2);

    // 3) Two different elements
    vector<int> tc3 = {1, 2};
    testCases.push_back(tc3);

    // 4) All identical elements
    vector<int> tc4(50, 5);
    testCases.push_back(tc4);

    // 5) Alternating two values
    vector<int> tc5;
    tc5.reserve(60);
    for (int i = 0; i < 60; ++i) tc5.push_back((i % 2) ? 2 : 1);
    testCases.push_back(tc5);

    // 6) Increasing sequence
    vector<int> tc6;
    tc6.reserve(100);
    for (int i = 1; i <= 100; ++i) tc6.push_back(i);
    testCases.push_back(tc6);

    // 7) Decreasing sequence
    vector<int> tc7;
    tc7.reserve(200);
    for (int i = 200; i >= 1; --i) tc7.push_back(i);
    testCases.push_back(tc7);

    // 8) Pseudo-random with quadratic formula modulo 25 (lots of duplicates)
    vector<int> tc8;
    tc8.reserve(200);
    for (int i = 0; i < 200; ++i) {
        long long val = (1LL * i * i + 7LL * i + 13LL) % 25LL;
        tc8.push_back((int)val);
    }
    testCases.push_back(tc8);

    // 9) Extremes and small values repeated
    vector<int> tc9;
    tc9.reserve(100);
    for (int i = 0; i < 25; ++i) {
        tc9.push_back(INT_MAX);
        tc9.push_back(INT_MIN);
        tc9.push_back(0);
        tc9.push_back(-1);
    }
    testCases.push_back(tc9);

    // 10) Linear congruential-like sequence modulo 50
    vector<int> tc10;
    tc10.reserve(300);
    for (int i = 0; i < 300; ++i) {
        tc10.push_back((i * 37 + 23) % 50);
    }
    testCases.push_back(tc10);

    Solution sol;

    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < testCases.size(); ++i) {
            int res = sol.subsequencesWithMiddleMode(testCases[i]);
            // Mix into checksum to avoid optimization
            checksum ^= (unsigned long long)res + 0x9e3779b97f4a7c15ull + (checksum << 6) + (checksum >> 2);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}