int main() {
    vector<pair<string, string>> tests = {
        {"1", "1"},
        {"2", "3"},
        {"4", "9"},
        {"1", "1000"},
        {"10", "10000"},
        {"100", "100000"},
        {"400", "500"},
        {"121", "484"},
        {"1000000", "100000000"},
        {"5000000000", "6000000000"}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (const auto& pr : tests) {
            checksum += sol.superpalindromesInRange(pr.first, pr.second);
        }
        sink = checksum;
    }

    return 0;
}