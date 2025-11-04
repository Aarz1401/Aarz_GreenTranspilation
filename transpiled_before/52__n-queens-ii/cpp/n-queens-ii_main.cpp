int main() {
    Solution sol;

    // 10 diverse integer inputs covering edge and typical cases
    const std::array<int, 10> tests = {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8};

    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : tests) {
            checksum += static_cast<uint64_t>(sol.totalNQueens(n));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";

    return 0;
}