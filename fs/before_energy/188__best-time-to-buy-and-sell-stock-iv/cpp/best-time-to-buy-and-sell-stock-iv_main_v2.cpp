int main() {
    std::vector<TestCase> tests = {
        {2, {3, 2, 6, 5, 0, 3}},
        {100, {1, 2, 3, 4, 5, 6}},
        {0, {1, 3, 2, 8, 4, 9}},
        {5, {5}},
        {3, {2, 4, 1, 7, 5, 3, 6, 4}},
        {4, {1, 5, 1, 5, 1, 5, 1}},
        {10, {9, 8, 7, 6, 5, 4, 3, 2, 1}},
        {2, {5, 1, 5, 1, 5}},
        {1, {1, 2, 3, 2, 5, 7, 2, 4, 9, 0}},
        {3, {3, 3, 5, 0, 0, 3, 1, 4, 2, 6, 4, 7, 2, 5, 1, 8}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tc : tests) {
            checksum += sol.maxProfit(tc.k, tc.prices);
        }
        sink = checksum;
    }

    return 0;
}