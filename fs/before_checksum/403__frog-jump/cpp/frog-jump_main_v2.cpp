int main() {
    std::vector<std::vector<int>> tests = {
        {0,1,3,5,6,8,12,17},
        {0,1,2,3,4,8,9,11},
        {0,1},
        {0,2},
        {0,1,2,4,7,11,16,22,29},
        {0,1,3,6,10,15,16,21},
        {0,1,3,4,5,7,9,10,12},
        {0,1,2,3,4,5,6,7,8,9,10},
        {0,1,4,9,16,25,36,49,64,81,100},
        {0,1,2,3,5,8,12,17,23,30}
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += s.canCross(t) ? 1 : 0;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}