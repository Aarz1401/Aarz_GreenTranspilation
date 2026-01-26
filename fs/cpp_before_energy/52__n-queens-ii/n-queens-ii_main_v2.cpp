int main() {
    Solution sol;
    std::vector<int> tests = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int n : tests) {
            checksum += sol.totalNQueens(n);
        }
        sink = checksum;
    }

    return 0;
}