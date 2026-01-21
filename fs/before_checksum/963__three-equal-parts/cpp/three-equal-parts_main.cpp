int main() {
    // Define 10 diverse test inputs
    vector<vector<int>> tests;

    // 1) Empty array
    tests.push_back({});

    // 2) Single zero
    tests.push_back({0});

    // 3) Single one (not divisible by 3)
    tests.push_back({1});

    // 4) All zeros
    tests.push_back({0, 0, 0, 0, 0});

    // 5) Not divisible by 3
    tests.push_back({1, 1, 0});

    // 6) Valid classic example
    tests.push_back({1, 0, 1, 0, 1});

    // 7) Valid "100" repeated
    tests.push_back({1, 0, 0, 1, 0, 0, 1});

    // 8) Valid "110" pattern repeated
    tests.push_back({1, 1, 0, 1, 1, 0, 1, 1, 0});

    // 9) Likely invalid due to trailing zeros mismatch
    tests.push_back({1, 0, 1, 0, 1, 0, 0});

    // 10) Large valid with long trailing zeros alignment
    {
        vector<int> big;
        big.insert(big.end(), 500, 0);
        big.push_back(1);
        big.insert(big.end(), 500, 0);
        big.push_back(1);
        big.insert(big.end(), 500, 0);
        big.push_back(1);
        big.insert(big.end(), 500, 0);
        tests.push_back(move(big));
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<int> res = sol.threeEqualParts(tests[i]);
            // Combine results into checksum to avoid optimization
            checksum += ((static_cast<long long>(res[0]) << 32) ^ (static_cast<unsigned long long>(res[1]) & 0xffffffffULL)) + static_cast<long long>(i) + iter;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}