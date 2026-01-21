int main() {
    vector<Test> tests = {
        {{"1","3","5","7"}, 100},
        {{"1","4","9"}, 1000000000},
        {{"7"}, 7},
        {{"1","2","3","4","5","6","7","8","9"}, 999999999},
        {{"2","5","8"}, 256},
        {{"3","4"}, 30},
        {{"9"}, 1000},
        {{"2","3","5","7"}, 50000000},
        {{"1","2"}, 1},
        {{"6","7","8","9"}, 68}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.atMostNGivenDigitSet(tests[i].D, tests[i].N);
        }
        sink = checksum;
    }

    return 0;
}