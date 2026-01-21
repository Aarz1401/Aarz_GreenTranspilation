int main() {
    vector<pair<string, string>> tests = {
        {"a", "a"},
        {"abc", "def"},
        {"abc", "cba"},
        {"abccba", "abc"},
        {"abcdefg", "gfedcba"},
        {"aaaaaaa", "aaaa"},
        {"banana", "ananas"},
        {"abaxyzzyxf", "xyzz"},
        {"thequickbrownfox", "xofnworbkciuqeht"},
        {"palindromeemordnilap", "levelrotor"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            checksum += sol.longestPalindrome(tc.first, tc.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}