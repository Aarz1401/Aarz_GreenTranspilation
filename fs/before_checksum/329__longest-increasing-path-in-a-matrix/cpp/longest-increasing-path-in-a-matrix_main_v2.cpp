int main() {
    vector<vector<vector<int>>> tests = {
        {{42}},
        {{7, 7, 7}, {7, 7, 7}},
        {{1, 2, 3, 4, 5}},
        {{1}, {2}, {3}, {4}, {5}},
        {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}},
        {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}},
        {{1, 2, 3, 4}, {12, 13, 14, 5}, {11, 16, 15, 6}, {10, 9, 8, 7}},
        {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}},
        {{-1, -2, -3}, {-2, -3, -4}, {-3, -4, -5}},
        {{1, 2, 1, 2}, {2, 1, 2, 1}, {1, 2, 1, 2}, {2, 1, 2, 1}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t t = 0; t < tests.size(); ++t) {
            checksum += sol.longestIncreasingPath(tests[t]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}