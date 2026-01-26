int main() {
    Solution s;
    vector<vector<int>> tests = {
        {5},
        {9,7,4,3,1},
        {1,2,3,4,5},
        {3,3,5,0,0,3,1,4},
        {1,2,4,2,5,7,2,4,9,0},
        {5,2,4,0,1,3,2,5},
        {1000000,1,1000000,1,1000000},
        {2,2,2,2,2},
        {1,3,2,8,4,9},
        {7,6,4,3,1,2,10,1,2,3,0,8}
    };

    const int iterations = 1000;
    volatile int sink = 0;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += s.maxProfit(tests[i]);
        }
        sink = checksum;
    }
    return 0;
}