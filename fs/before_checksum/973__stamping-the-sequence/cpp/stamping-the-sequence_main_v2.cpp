int main() {
    vector<pair<string, string>> tests = {
        {"abca", "aabcaca"},
        {"abc", "ababc"},
        {"a", "aaaaa"},
        {"aa", "aaaa"},
        {"xyz", "xyzxyzxyz"},
        {"aba", "ababa"},
        {"z", "zzzzzz"},
        {"abcde", "abcde"},
        {"abc", "abcabc"},
        {"aba", "abaaba"}
    };

    Solution s;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            auto res = s.movesToStamp(t.first, t.second);
            checksum += static_cast<int>(res.size());
            for (int v : res) {
                checksum += v;
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}