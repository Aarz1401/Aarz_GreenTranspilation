int main() {
    // Generate diverse test inputs
    std::vector<TestCase> tests;
    // 1. Empty array
    tests.push_back(TestCase{{}, 5, 3});
    // 2. Single element
    tests.push_back(TestCase{{10}, 0, 0});
    // 3. All equal
    tests.push_back(TestCase{{5, 5, 5, 5, 5}, 0, 0});
    // 4. Increasing with small k
    tests.push_back(TestCase{{1, 2, 4, 7, 7, 8, 12}, 2, 2});
    // 5. Negative and positive values
    tests.push_back(TestCase{{-10, -8, -7, -3, 0, 1, 2, 9}, 3, 3});
    // 6. Large k dominates distances
    tests.push_back(TestCase{{1, 100, 200, 300, 400, 500}, 1000, 2});
    // 7. Many duplicates with a small window
    tests.push_back(TestCase{{1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 4}, 1, 3});
    // 8. Zero k with large operations
    tests.push_back(TestCase{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 0, 100});
    // 9. Larger patterned array
    {
        std::vector<int> arr9;
        for (int i = 0; i < 120; ++i) {
            int v = (i * i * 31) % 2001 - 1000; // values in [-1000, 1000]
            arr9.push_back(v);
        }
        tests.push_back(TestCase{arr9, 10, 20});
    }
    // 10. Extreme integer values
    tests.push_back(TestCase{{INT_MIN, INT_MIN + 1, -1, 0, 1, INT_MAX - 1, INT_MAX}, 2, 3});

    Solution sol;
    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            std::vector<int> numsCopy = tc.nums; // ensure sort cost each iteration
            int res = sol.maxFrequency(numsCopy, tc.k, tc.ops);
            checksum += res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";

    return 0;
}