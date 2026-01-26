int main() {
    vector<vector<int>> tests = {
        {4, 1, 8, 7},  // true
        {1, 2, 3, 4},  // true
        {3, 3, 8, 8},  // true
        {6, 6, 6, 6},  // true
        {1, 3, 4, 6},  // true
        {9, 1, 3, 4},  // true
        {7, 3, 1, 5},  // true
        {1, 1, 1, 1},  // false
        {2, 2, 2, 2},  // false
        {1, 1, 2, 2}   // false
    };

    Solution s;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& v : tests) {
            checksum += s.judgePoint24(v);
        }
        sink = checksum;
    }
    return 0;
}