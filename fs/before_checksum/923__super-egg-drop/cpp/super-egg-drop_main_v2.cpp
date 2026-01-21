int main() {
    std::vector<std::pair<int,int>> tests = {
        {1, 1},
        {1, 10000},
        {2, 100},
        {3, 14},
        {10, 10000},
        {100, 10000},
        {2, 1},
        {3, 1000},
        {4, 500},
        {8, 2000}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.superEggDrop(t.first, t.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}