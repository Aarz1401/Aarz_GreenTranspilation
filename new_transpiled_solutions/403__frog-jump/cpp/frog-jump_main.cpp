int main() {
    std::vector<std::vector<int>> tests = {
        {0},
        {0, 1},
        {0, 2},
        {0, 1, 3, 5, 6, 8, 12, 17},
        {0, 1, 2, 3, 4, 8, 9, 11},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {0, 1, 3, 4, 5, 7, 9, 10, 12},
        {0, 1, 3, 6, 10, 13, 14},
        {0, 1, 4, 5, 9, 10, 13, 17},
        {0, 1, 2, 4, 7, 11, 16, 22, 29, 37}
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            bool res = sol.canCross(tests[i]);
            checksum += res ? (static_cast<long long>(tests[i].size()) + iter + static_cast<long long>(i)) 
                            : static_cast<long long>(i);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed << "\n";
    return 0;
}