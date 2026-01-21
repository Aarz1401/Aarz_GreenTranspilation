int main() {
    // Prepare 10 diverse test inputs
    std::vector<std::vector<int>> tests;
    tests.reserve(10);

    // 1) Empty
    tests.push_back({});

    // 2) Single element
    tests.push_back({5});

    // 3) Two elements (no trapping)
    tests.push_back({2, 1});

    // 4) Monotonic increasing
    tests.push_back({0, 1, 2, 3, 4, 5, 6});

    // 5) Monotonic decreasing
    tests.push_back({6, 5, 4, 3, 2, 1, 0});

    // 6) Simple valley
    tests.push_back({5, 0, 0, 0, 5});

    // 7) Canonical LeetCode example
    tests.push_back({0,1,0,2,1,0,1,3,2,1,2,1});

    // 8) Plateaus and dips
    tests.push_back({3,3,3,1,2,1,3,1,0,1,2,2,3});

    // 9) Alternating peaks and valleys
    tests.push_back({2,0,2,0,2,0,2,0,2});

    // 10) Larger patterned input
    std::vector<int> big;
    big.reserve(210);
    for (int rep = 0; rep < 10; ++rep) {
        for (int i = 0; i <= 9; ++i) big.push_back(i);
        for (int i = 10; i >= 0; --i) big.push_back(i);
    }
    tests.push_back(std::move(big));

    Solution sol;

    volatile uint64_t checksum = 0; // volatile to further prevent optimization

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& test : tests) {
            checksum += static_cast<uint64_t>(sol.trap(test));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}