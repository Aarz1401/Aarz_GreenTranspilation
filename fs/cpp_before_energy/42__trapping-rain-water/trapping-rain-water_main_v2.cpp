int main() {
    std::vector<std::vector<int>> tests = {
        {0,1,0,2,1,0,1,3,2,1,2,1},
        {0,1,2,3,4,5,6,7},
        {7,6,5,4,3,2,1,0},
        {2,2,2,2,2},
        {5,0,5},
        {4,2,0,3,2,5},
        {3,0,2,0,4},
        {0,0,0,0},
        {9,1,8,0,7,2,6,3,5,4,4,5,3,6,2,7,0,8,1,9},
        {1,3,2,1,2,1,5,2,2,1,4,2,2,1,0,1,2,3,4,0,2}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& h : tests) {
            checksum += sol.trap(h);
        }
        sink = checksum;
    }

    return 0;
}