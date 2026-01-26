int main() {
    std::vector<int> tests = {1, 2, 3, 4, 5, 10, 50, 100, 1000, 100000};

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int n : tests) {
            long long res = sol.checkRecord(n);
            checksum = static_cast<int>((checksum + res) % 2147483647);
        }
        sink = checksum;
    }

    return 0;
}