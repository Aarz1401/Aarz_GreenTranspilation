int main() {
    vector<vector<int>> tests = {
        {1, 2},
        {1, 2, 3, 4, 5, 6, 7, 8},
        {5, 5, 5, 5},
        {0, 0, 0, 0, 0, 0, 0},
        {2, 0, 5, 6, 16, 12, 15, 9},
        {3, 3, 3, 4, 5},
        {1, 2, 3, 4, 6, 8, 10},
        {9, 1, 2, 3, 4, 5, 6, 7, 8},
        {1, 1, 1, 1, 1, 1},
        {10, 20, 30, 40, 50, 60}
    };

    Solution s;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& A : tests) {
            checksum += s.splitArraySameAverage(A) ? 1 : 0;
        }
        sink = checksum;
    }
    return 0;
}