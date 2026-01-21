int main() {
    vector<vector<int>> tests = {
        {0},
        {1, 0},
        {2, 2, 1},
        {0, 0, 0, 0},
        {4, 3, 2, 1, 0},
        {0, 1, 2, 3, 4, 5},
        {6, 5, 4, 3, 2, 1, 0},
        {1, 3, 5, 7, 0, 2, 4, 6},
        {2, 0, 6, 3, 1, 4, 9, 7, 5, 8},
        {14, 0, 14, 7, 3, 5, 10, 2, 12, 6, 8, 1, 9, 4, 11}
    };

    Solution s;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += s.bestRotation(t);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}