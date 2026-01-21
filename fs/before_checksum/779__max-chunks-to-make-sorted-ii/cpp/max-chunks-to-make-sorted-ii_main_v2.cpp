int main() {
    vector<vector<int>> tests = {
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {1, 1, 1, 1},
        {2, 1, 3, 4, 4},
        {2, 2, 1, 1, 3, 3},
        {-2, -1, -3, 4, 3},
        {0},
        {1, 0, 1, 3, 2},
        {1000000000, -1000000000, 0, 999999999, -999999999},
        {1, 3, 2, 2, 2}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (auto& t : tests) {
            checksum += sol.maxChunksToSorted(t);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}