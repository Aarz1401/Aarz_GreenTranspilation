int main() {
    vector<vector<int>> tests = {
        {0,0,0,0,0,0},
        {1,0,1,0,1},
        {1,1,0,1,1},
        {1,0,0,1,0,0,1},
        {1,0,1,0,1,0,0,0,0},
        {0,1,0,1,0,1,0},
        {1,1,1,0,0,0},
        {1,0,0,0,1,0,0,0,1,0,0,0},
        {0,0,1,1,0,1,0,0},
        {1,0,1,1,0,1,0,1,0,1,0,0}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            auto res = sol.threeEqualParts(tests[i]);
            checksum += res[0];
            checksum += res[1];
        }
        sink = checksum;
    }

    return 0;
}