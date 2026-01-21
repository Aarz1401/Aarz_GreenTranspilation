int main() {
    Solution sol;
    const std::vector<int> tests = {1, 2, 3, 6, 7, 8, 9, 15, 31, 10000};

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int t : tests) {
            checksum += sol.racecar(t);
        }
        sink = checksum;
    }

    return 0;
}