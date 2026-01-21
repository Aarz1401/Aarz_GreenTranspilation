int main() {
    std::vector<InputCase> tests = {
        {0, 0, 0},
        {1, 1, 1},
        {2, 3, 5},
        {10, 10, 0},
        {50, 20, 7},
        {200, 500, 1000},
        {1000, 1000, 1000},
        {999, 1000, 2},
        {100, 1, 999},
        {345, 678, 123}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            checksum += sol.numberOfWays(tc.n, tc.x, tc.y);
        }
        sink = checksum;
    }

    return 0;
}