int main() {
    vector<pair<vector<int>, int>> tests = {
        {{1}, 0},
        {{2}, 0},
        {{3, 6, 12, 24, 5, 10}, 1},
        {{7, 7, 7, 7}, 0},
        {{8, 4, 2, 1, 16, 32}, 2},
        {{9, 15, 21, 27, 33, 39, 45}, 3},
        {{100000, 50000, 25000, 12500}, 1},
        {{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, 0},
        {{6, 10, 14, 22, 26, 34, 38}, 2},
        {{12, 18, 4, 9, 2, 3, 8, 6, 5, 7}, 1}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<int> v = t.first;
            int k = t.second;
            long long r = sol.maxGCDScore(v, k);
            checksum += static_cast<int>(r);
        }
        sink = checksum;
    }

    return 0;
}