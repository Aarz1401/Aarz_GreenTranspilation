int main() {
    vector<long long> tests = {
        0LL,
        1LL,
        21LL,
        333LL,
        4444LL,
        123456LL,
        2222222LL,
        9999999999LL,
        7000000000000000LL,
        8888666226668887LL
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (long long n : tests) {
            long long res = sol.specialPalindrome(n);
            checksum ^= static_cast<int>(res);
        }
        sink = checksum;
    }

    return 0;
}