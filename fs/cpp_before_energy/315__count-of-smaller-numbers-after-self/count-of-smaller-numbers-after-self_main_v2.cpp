int main() {
    vector<vector<int>> tests = {
        {1, 2, 3, 4},
        {4, 3, 2, 1},
        {5, 5, 5, 5},
        {2, 0, 1, 2, 0},
        {7},
        {1, 3, 2, 3, 1},
        {-10, -10, 0, 10, -5, 5},
        {10000, -10000, 0, 9999, -9999, 5000, -5000, 123, -123, 0},
        {0, 0, 1, 0, -1},
        {3, 1, 2, 2, 1, 3, 0}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int t = 0; t < static_cast<int>(tests.size()); ++t) {
            vector<int> res = sol.countSmaller(tests[t]);
            for (int v : res) {
                checksum += v;
            }
        }
        sink = checksum;
    }

    return 0;
}