int main() {
    std::vector<std::vector<int>> tests = {
        {1},
        {2, 2},
        {1, 2},
        {1, 2, 3},
        {5, 5, 5},
        {1, 3, 1},
        {1, 1, 2, 2, 1},
        {1, 2, 2, 2, 1},
        {1, 3, 2, 2, 3, 1},
        {2, 2, 1, 3, 3, 1, 2}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += sol.removeBoxes(t);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}