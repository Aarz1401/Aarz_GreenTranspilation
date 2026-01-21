int main() {
    std::vector<std::vector<int>> tests = {
        {2, 1, 1, 2},                                  // crossing
        {1, 2, 3, 4},                                  // non-crossing
        {1, 1, 1, 1},                                  // crossing
        {1, 1, 2, 1, 1},                               // crossing (special early check)
        {1, 2, 3, 4, 2, 2},                            // crossing (case 2)
        {2, 2, 3, 3, 2, 2},                            // crossing (case 2)
        {100000000, 200000000, 300000000, 400000000, 500000000, 600000000}, // non-crossing
        {3, 4, 5, 6, 7, 8},                            // non-crossing
        {1, 2, 3, 2},                                  // non-crossing
        {2, 1, 3, 2, 4, 3}                             // non-crossing
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += sol.isSelfCrossing(t) ? 1 : 0;
        }
        sink = checksum;
    }

    return 0;
}