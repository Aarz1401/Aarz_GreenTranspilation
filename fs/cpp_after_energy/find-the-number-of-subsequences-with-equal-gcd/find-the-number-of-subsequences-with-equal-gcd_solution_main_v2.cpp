int main() {
    vector<vector<int>> tests = {
        {1},
        {1, 1, 1, 1},
        {2, 3, 4, 6},
        {2, 3, 5, 7, 11},
        {1, 2, 4, 8, 16, 32},
        {6, 12, 18, 24, 30},
        {10, 10, 10, 10, 10, 10, 10},
        {3, 6, 9, 12, 15, 21, 27},
        {4, 9, 25, 49},
        {5, 10, 20, 4, 8, 16, 3, 6, 12}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += sol.subsequencePairCount(t);
        }
        sink = checksum;
    }

    return 0;
}