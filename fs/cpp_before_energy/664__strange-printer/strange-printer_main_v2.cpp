int main() {
    vector<string> tests = {
        "a",
        "aaaaaaa",
        "ab",
        "aba",
        "abcabcabc",
        "aaabbbccc",
        "abaabbba",
        "abcdedcba",
        "bacabacaba",
        "thequickbrownfox"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.strangePrinter(s);
        }
        sink = checksum;
    }

    return 0;
}