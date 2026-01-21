int main() {
    vector<string> tests = {
        "a",
        "aa",
        "ab",
        "abcd",
        "aacecaaa",
        "racecar",
        "ababbbabbaba",
        "xyzzyxabc",
        "zzzzzz",
        "abcdabc"
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        Solution sol;
        int checksum = 0;
        for (const auto& s : tests) {
            string r = sol.shortestPalindrome(s);
            checksum += static_cast<int>(r.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}