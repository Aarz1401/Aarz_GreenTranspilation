int main() {
    std::vector<int> tests = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2};

    Solution sol;

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;

        for (int n : tests) {
            auto res = sol.solveNQueens(n);
            checksum += static_cast<int>(res.size());
        }

        sink = checksum;
    }

    return 0;
}