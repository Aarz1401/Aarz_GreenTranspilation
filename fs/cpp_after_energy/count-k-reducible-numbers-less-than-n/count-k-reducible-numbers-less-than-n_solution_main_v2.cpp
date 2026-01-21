int main() {
    vector<pair<string,int>> tests = {
        {"1", 1},
        {"0", 1},
        {"10", 1},
        {"10101", 2},
        {"11111", 3},
        {"00000", 1},
        {"110010100111", 2},
        {"10101010101010101010101010101010", 1},
        {"1001001001001001001", 2},
        {"111000111000111000111000111000111000111000111000111000111000", 4}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            checksum += sol.countKReducibleNumbers(tc.first, tc.second);
        }
        sink = checksum;
    }

    return 0;
}