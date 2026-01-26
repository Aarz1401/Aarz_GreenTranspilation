int main() {
    vector<string> tests = {
        "10",
        "1100",
        "1010",
        "111000",
        "110100",
        "110010",
        "11100100",
        "11011000",
        "1011001100",
        "1101101000"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            string r = sol.makeLargestSpecial(s);
            checksum += static_cast<int>(r.size());
        }
        sink = checksum;
    }

    return 0;
}