int main() {
    // Define 10 diverse test cases
    std::vector<InputCase> tests = {
        {0, 0, 0},
        {0, 1000, 1000},
        {1, 1, 1},
        {10, 3, 2},
        {100, 50, 7},
        {500, 500, 1000},
        {1000, 1000, 999},
        {1000, 1, 1000},
        {1, 1000, 500},
        {999, 750, 0}
    };

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            int res = sol.numberOfWays(tc.n, tc.x, tc.y);
            checksum ^= (static_cast<uint64_t>(res) + 0x9e3779b97f4a7c15ull + (checksum << 6) + (checksum >> 2));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}