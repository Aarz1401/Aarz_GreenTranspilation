int main() {
    vector<int> tests = {1, 2, 3, 4, 1, 2, 3, 4, 2, 3};

    Solution sol;

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int n : tests) {
            checksum += sol.largestPalindrome(n);
        }
        sink = checksum;
    }

    return 0;
}