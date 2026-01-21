int main() {
    vector<vector<vector<int>>> tests = {
        {{0}},
        {{5}},
        {{1, 2}},
        {{1}, {2}},
        {{1, 2}, {3, 4}},
        {{1, 1, 1}, {1, 1, 1}},
        {{3, 1, 2}, {4, 0, 5}, {6, 7, 8}},
        {{10, 20, 30, 40}},
        {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
        {{9, 8, 7, 6}, {5, 4, 3, 2}, {1, 0, 1, 0}}
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& grid : tests) {
            checksum += s.canPartitionGrid(grid);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}