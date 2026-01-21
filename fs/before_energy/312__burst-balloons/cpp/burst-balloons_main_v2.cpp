int main() {
    std::vector<std::vector<int>> tests = {
        {3, 1, 5, 8},
        {1},
        {9, 76, 64, 21},
        {1, 5},
        {7, 0, 2, 0, 9},
        {8, 2, 6, 8, 1, 4},
        {2, 2, 2, 2, 2, 2, 2, 2},
        {100, 1, 100, 1, 100},
        {2, 4, 3, 5, 1, 2},
        {1, 0, 3, 0, 5, 0, 8, 0, 13, 0, 21}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (auto& t : tests) {
            checksum += sol.maxCoins(t);
        }
        sink = checksum;
    }

    return 0;
}