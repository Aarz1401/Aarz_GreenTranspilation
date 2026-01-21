int main() {
    vector<TestCase> tests = {
        {"0", "0", 2},
        {"0", "9", 10},
        {"10", "99", 10},
        {"1", "1000000", 3},
        {"123456789012345678", "987654321098765432", 7},
        {"100000000000000000000000", "100000000000000000000500", 2},
        {"255", "255", 16},
        {"100", "1000", 4},
        {"999999999999999999", "1000000000000000000", 5},
        {"3141592653589793", "3141592653589793238", 9}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            checksum += sol.countNumbers(tc.l, tc.r, tc.b);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}