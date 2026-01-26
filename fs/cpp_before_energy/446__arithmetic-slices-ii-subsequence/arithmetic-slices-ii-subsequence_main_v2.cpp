int main() {
    std::vector<std::vector<int>> tests = {
        {1, 2, 3},
        {2, 4, 6, 8, 10},
        {7, 7, 7, 7, 7},
        {1, 1, 2, 2, 3, 3},
        {1, 3, 5, 7, 9, 11, 13},
        {1, 5, 9, 2, 6, 10, 3, 7, 11},
        {0, -1, -2, -3, -4},
        {1, 2, 4, 8, 16, 32},
        {1000000000, -1000000000, 0, -1000000000, 1000000000},
        {1, 4, 7, 10, 13, 2, 5, 8, 11, 14, 17, 20}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& A : tests) {
            checksum += sol.numberOfArithmeticSlices(A);
        }
        sink = checksum;
    }

    return 0;
}