int main() {
    std::vector<int> test_inputs = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    Solution solver;
    volatile uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : test_inputs) {
            auto res = solver.solveNQueens(n);
            checksum += static_cast<uint64_t>(res.size());
            for (const auto& board : res) {
                for (const auto& row : board) {
                    auto pos = row.find('Q');
                    if (pos != std::string::npos) {
                        checksum += static_cast<uint64_t>(pos + 1);
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed << "\n";
    return 0;
}