int main() {
    std::vector<std::vector<int>> tests = {
        {1},
        {2, 2, 2, 2, 2},
        {3, 4, 5, 1, 2},
        {2, 2, 2, 3, 1, 2},
        {10, 1, 10, 10, 10},
        {1, 2, 3, 4, 5, 6, 7},
        {2, 2, 3, 4, 4, 5, 1, 1, 2},
        {5, 6, 7, 0, 1, 2, 3, 4},
        {4, 4, 4, 5, 6, 7, 0, 1, 2, 2, 3},
        {0, 0, 1, 2, 2, 2, 2, 2, 0}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += sol.findMin(t);
        }
        sink = checksum;
    }

    return 0;
}