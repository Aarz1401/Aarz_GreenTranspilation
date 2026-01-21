int main() {
    // Define 10 diverse test inputs
    std::vector<std::vector<int>> tests;
    tests.push_back({}); // empty
    tests.push_back({7}); // single element
    tests.push_back({1, 2}); // two different
    tests.push_back({1, 1, 1, 1, 1}); // all same
    tests.push_back({1, 2, 3, 4, 5, 6}); // all distinct, increasing
    tests.push_back({1, 1, 2, 2, 3, 3, 4, 4}); // pairs
    tests.push_back({1, 2, 2, 2, 1}); // merge same ends via middle block
    tests.push_back({3, 3, 2, 1, 2, 3, 3}); // symmetric groups with merges
    tests.push_back({1, 2, 1, 2, 1, 2, 1}); // alternating
    tests.push_back({1, 1, 1, 2, 2, 3, 3, 3, 2, 2, 1, 1}); // larger mixed groups

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            int result = sol.removeBoxes(t);
            checksum += static_cast<uint64_t>(result);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}