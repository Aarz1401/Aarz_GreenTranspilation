int main() {
    vector<vector<vector<int>>> tests = {
        {{0, 0, 10}},
        {{0, 0, 2}, {0, 4, 2}},
        {{0, 0, 4}, {2, 1, 4}},
        {{0, 0, 3}, {3, 0, 2}, {6, 0, 1}},
        {{0, 0, 10}, {2, 2, 6}, {4, 4, 2}},
        {{-5, -5, 10}},
        {{0, 0, 2}, {2, 0, 2}, {0, 2, 2}, {2, 2, 2}},
        {{0, 0, 3}, {10, 1, 5}, {20, 2, 4}},
        {{0, 0, 4}, {1, 0, 4}, {2, 0, 4}},
        {{1000000000, 100000000, 1000000000}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tc : tests) {
            double r = sol.separateSquares(tc);
            checksum += static_cast<int>(r);
        }
        sink = checksum;
    }

    return 0;
}