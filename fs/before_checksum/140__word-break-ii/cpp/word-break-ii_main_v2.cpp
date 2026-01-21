int main() {
    std::vector<Test> tests = {
        {"catsanddog", {"cat","cats","and","sand","dog"}},
        {"pineapplepenapple", {"apple","pen","applepen","pine","pineapple"}},
        {"aaaaaaa", {"a","aa","aaa"}},
        {"leetcode", {"leet","code"}},
        {"catsandog", {"cats","dog","sand","and","cat"}},
        {"abcd", {"a","abc","b","cd"}},
        {"aaaaab", {"a","aa","aaa","aaaa","b"}},
        {"bb", {"a","b","bbb","bbbb"}},
        {"foobarbaz", {"foo","bar","baz","foobar","barbaz","foob","arb","az"}},
        {"impossible", {"im","possible","impo","ss","ible"}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            auto res = sol.wordBreak(t.s, t.dict);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}