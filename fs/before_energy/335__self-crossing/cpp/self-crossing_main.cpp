int main() {
    // Define 10 diverse test cases
    std::vector<std::vector<int>> tests = {
        {2, 1, 1, 2},                                  // crossing (case 1)
        {1, 2, 3, 4, 5, 6},                            // non-crossing
        {1, 1, 2, 1, 1},                               // crossing (overlapped pre-check)
        {1, 1, 2, 2, 1, 1},                            // crossing (case 2)
        {1, 1, 1, 1},                                  // crossing
        {1, 1, 2, 3, 4, 5},                            // non-crossing
        {},                                            // empty (non-crossing)
        {5},                                           // single element (non-crossing)
        {0, 0, 0, 0},                                  // zeros (crossing)
        {1500000000, 1500000000, 1, 1500000000, 1500000000} // large numbers (overlapped pre-check)
    };

    Solution solver;

    long long checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            bool res = solver.isSelfCrossing(tests[i]);
            checksum += res ? static_cast<long long>(i + 1) : 0;
        }
    }

    auto end = Clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}