int main() {
    vector<vector<vector<int>>> tests = {
        {{0}},
        {{1}},
        {{0,0},{0,0}},
        {{1,1},{1,1}},
        {{1,1,0},{1,0,1},{0,1,1}},
        {{1,1,1},{1,0,1},{1,1,1}},
        {{0,1,0,1},{1,0,1,0},{0,1,0,1},{1,0,1,0}},
        {{1,0,1,0,1},{0,1,1,0,0},{1,1,0,0,1},{0,0,0,1,1},{1,0,1,1,0}},
        {{1,0},{0,1}},
        {{1,1,1,1,1},{1,1,0,1,1},{1,0,0,0,1},{1,1,0,1,1},{1,1,1,1,1}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            auto grid = tests[i];
            checksum += sol.largestIsland(grid);
        }
        sink = checksum;
    }

    return 0;
}