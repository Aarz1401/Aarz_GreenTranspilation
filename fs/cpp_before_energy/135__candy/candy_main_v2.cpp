int main() {
    Solution sol;
    std::vector<std::vector<int>> tests = {
        {1},
        {1,2,3,4,5},
        {5,4,3,2,1},
        {1,0,2},
        {1,2,2},
        {2,2,2,2,2},
        {1,3,4,5,2},
        {1,3,2,2,1},
        {1,6,10,8,7,3,2},
        {1,2,87,87,87,2,1}
    };

    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.candy(tests[i]);
        }
        sink = checksum;
    }

    return 0;
}