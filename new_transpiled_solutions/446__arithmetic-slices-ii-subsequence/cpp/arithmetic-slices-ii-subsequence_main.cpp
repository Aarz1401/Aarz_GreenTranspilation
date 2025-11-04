int main() {
    // Prepare 10 diverse test cases
    std::vector<std::vector<int>> tests;
    tests.reserve(10);

    // 1. Empty array
    tests.push_back({});

    // 2. Single element
    tests.push_back({42});

    // 3. Two elements
    tests.push_back({1, 2});

    // 4. Simple arithmetic progression of length 3
    tests.push_back({1, 3, 5});

    // 5. Non-arithmetic triple
    tests.push_back({1, 4, 9});

    // 6. All equal elements
    tests.push_back({7, 7, 7, 7});

    // 7. Mixed negatives and positives with constant step
    tests.push_back({-5, -1, 3, 7, 11});

    // 8. Large values near INT_MAX to test diff handling
    tests.push_back({INT_MAX, INT_MAX - 1, INT_MAX - 2, INT_MAX - 3});

    // 9. Longer arithmetic progression (even numbers)
    {
        std::vector<int> ap;
        for (int i = 0; i < 12; ++i) ap.push_back(i * 2);
        tests.push_back(std::move(ap));
    }

    // 10. Larger mixed dataset with various patterns
    tests.push_back({
        5, 1, 9, 3, 7, 13, 2, 8, 14, 0,
        6, 12, 4, 10, 11, 15, 20, 25, -5, -1,
        -9, 100, 105, 110, 115, 200, 195, 190, 180, 170,
        160, 150, 140, 130, 120, 300, 301, 303, 306, 310,
        -100, -90, -80, -70, -60, -50, -40, -30, -20, -10
    });

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.numberOfArithmeticSlices(tests[i]);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}