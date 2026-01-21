int main() {
    vector<string> inputs = {
        "a",
        "aa",
        "ab",
        "aba",
        "abcd",
        "dcbaabcd",
        "aaaaaaa",
        "abacabadabacaba",
        "abcdabcdabcdabcd",
        "abcdabcdabcdabcdabcdabcdabcdabcdabcdabcd"
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& in : inputs) {
            checksum += s.countPalindromicSubsequences(in);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}