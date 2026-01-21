int main() {
    std::vector<int> tests = {
        0, 1, 9, 10, 11, 19, 99, 101, 1000, 1000000000
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int n : tests) {
            checksum += sol.countDigitOne(n);
        }
        sink = checksum;
    }

    return 0;
}