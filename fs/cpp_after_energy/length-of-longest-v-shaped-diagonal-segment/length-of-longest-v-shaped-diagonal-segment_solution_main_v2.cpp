int main() {
    vector<vector<vector<int>>> tests = {
        {{1}},
        {{0}},
        {{2}},
        {
            {0, 2},
            {2, 0}
        },
        {
            {0, 2, 0},
            {2, 1, 2},
            {0, 2, 0}
        },
        {
            {1, 0, 2},
            {0, 2, 1},
            {2, 1, 0},
            {1, 2, 0}
        },
        {
            {0, 1, 2, 1, 0},
            {1, 0, 1, 0, 1},
            {2, 1, 0, 1, 2},
            {1, 0, 1, 0, 1},
            {0, 1, 2, 1, 0}
        },
        {
            {1, 0, 2},
            {0, 2, 0}
        },
        {
            {0, 2, 0, 2},
            {2, 0, 2, 0},
            {1, 1, 1, 1},
            {0, 2, 0, 2},
            {2, 0, 2, 0},
            {1, 0, 1, 2}
        },
        {
            {2, 0, 2, 0, 2},
            {1, 1, 1, 1, 1},
            {0, 2, 0, 2, 0}
        }
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += sol.lenOfVDiagonal(t);
        }
        sink = checksum;
    }
    return 0;
}