int main() {
    // Generate 10 diverse test inputs
    vector<vector<int>> tests;
    vector<int> ks;

    // 0: Empty array
    tests.push_back({});
    ks.push_back(0);

    // 1: Single element
    tests.push_back({1});
    ks.push_back(0);

    // 2: Small odds
    tests.push_back({3, 5, 7, 9, 11, 13, 15, 17});
    ks.push_back(1);

    // 3: Powers of two
    {
        vector<int> v;
        for (int i = 1; i <= 16; ++i) v.push_back(1 << i);
        tests.push_back(std::move(v));
        ks.push_back(4);
    }

    // 4: Mixed even composites
    tests.push_back({6, 10, 14, 22, 26, 30, 42, 60, 84, 98, 126, 150, 210, 330, 510, 1022});
    ks.push_back(3);

    // 5: Repeated elements with same 2-exponent
    {
        vector<int> v(24, 12); // 12 = 3 * 2^2
        tests.push_back(std::move(v));
        ks.push_back(2);
    }

    // 6: Sequential numbers
    {
        vector<int> v;
        for (int i = 1; i <= 40; ++i) v.push_back(i);
        tests.push_back(std::move(v));
        ks.push_back(5);
    }

    // 7: Deterministic pseudo-random with variable 2-exponent
    {
        vector<int> v;
        for (int i = 1; i <= 64; ++i) {
            uint32_t val = (static_cast<uint32_t>(i) * 97u) ^ (static_cast<uint32_t>(i) * 131u);
            int base = static_cast<int>(val % 1000000u) + 1;
            base <<= (i % 3);
            v.push_back(base);
        }
        tests.push_back(std::move(v));
        ks.push_back(0);
    }

    // 8: Primes (including 2)
    tests.push_back({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71});
    ks.push_back(2);

    // 9: Larger structured array with varying 2-exponents
    {
        vector<int> v;
        for (int i = 1; i <= 96; ++i) {
            int val = (i + 1) * (i % 7 + 1) * (1 << (i % 5)) + (i % 3);
            if (val <= 0) val = i + 1;
            v.push_back(val);
        }
        tests.push_back(std::move(v));
        ks.push_back(7);
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run all test cases each iteration
        for (size_t t = 0; t < tests.size(); ++t) {
            vector<int> nums = tests[t]; // copy because function mutates nums
            checksum += sol.maxGCDScore(nums, ks[t]);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = static_cast<double>(elapsed_ns) / 1e6;

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}