int main() {
    vector<string> tests = {
        "3",
        "4",
        "13",
        "31",
        "4681",
        "999999999999999999",
        "1000000000000000000",
        "2251799813685247",
        "1099511627775",
        "1000003"
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& n : tests) {
            string res = s.smallestGoodBase(n);
            checksum += static_cast<int>(res.size());
            checksum += static_cast<int>(res.back() - '0');
        }
        sink = checksum;
    }

    return 0;
}