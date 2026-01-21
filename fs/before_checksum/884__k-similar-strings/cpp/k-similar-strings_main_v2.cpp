int main() {
    std::vector<std::pair<std::string, std::string>> tests = {
        {"a", "a"},
        {"ab", "ba"},
        {"abc", "bca"},
        {"aabc", "abca"},
        {"abac", "baca"},
        {"aabbcc", "abcabc"},
        {"abcdef", "fabcde"},
        {"abcdef", "badcfe"},
        {"abababab", "babababa"},
        {"aaabbbccdd", "ddccbbaaab"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& p : tests) {
            checksum += sol.kSimilarity(p.first, p.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}