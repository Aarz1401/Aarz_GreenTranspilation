int main() {
    // Prepare 10 diverse test inputs
    std::vector<std::vector<int>> tests;
    tests.push_back({});                               // empty
    tests.push_back({1, 2, 0});                        // contains zero, missing 3
    tests.push_back({3, 4, -1, 1});                    // negatives and positives, missing 2
    tests.push_back({7, 8, 9, 11, 12});                // all > n, missing 1
    tests.push_back({1, 1});                           // duplicates of 1, missing 2
    tests.push_back({2, 2});                           // duplicates of 2, missing 1
    tests.push_back({1, 2, 3, 4, 5});                  // already 1..n, missing 6
    tests.push_back({2});                              // single element not 1, missing 1
    tests.push_back({1, 1, 0, -1, 2, 2, 4});           // mixed, missing 3

    // Large mixed test with one missing in range
    std::vector<int> largeTest;
    largeTest.reserve(20004);
    for (int i = 1; i <= 20000; ++i) {
        if (i != 5432) largeTest.push_back(i);         // missing 5432
    }
    largeTest.push_back(-1);
    largeTest.push_back(0);
    largeTest.push_back(1000000);
    largeTest.push_back(2);                            // duplicate
    tests.push_back(std::move(largeTest));

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t ti = 0; ti < tests.size(); ++ti) {
            std::vector<int> input = tests[ti]; // copy since algorithm mutates
            int result = sol.firstMissingPositive(input);
            checksum += result;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}