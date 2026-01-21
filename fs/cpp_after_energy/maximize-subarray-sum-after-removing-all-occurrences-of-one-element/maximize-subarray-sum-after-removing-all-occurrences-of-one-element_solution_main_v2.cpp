int main() {
    vector<vector<int>> tests = {
        {1, 2, 3, 4},
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},
        {-1, -2, -3, -4},
        {0, 0, 0, 0, 0},
        {1000, -100, 2000, -50, 3000},
        {5, -1, 5, -1, 5, -1, 5},
        {42},
        {-7},
        {3, -2, 5, -1, 6, -3, 2, 7, -5, 2},
        {10, -20, 30, -5, -5, 40, -10, 5}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            long long res = sol.maxSubarraySum(tests[i]);
            checksum += static_cast<int>(res);
        }
        sink = checksum;
    }
    return 0;
}