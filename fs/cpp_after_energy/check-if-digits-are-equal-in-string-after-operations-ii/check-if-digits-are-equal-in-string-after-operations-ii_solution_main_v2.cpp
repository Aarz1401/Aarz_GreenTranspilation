int main() {
    Solution sol;
    vector<string> tests = {
        "0",
        "9",
        "10",
        "01",
        "12345",
        "54321",
        "11111111",
        "9090909090",
        "314159265358979",
        "271828182845904"
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.hasSameDigits(s) ? 1 : 0;
        }
        sink = checksum;
    }

    return 0;
}