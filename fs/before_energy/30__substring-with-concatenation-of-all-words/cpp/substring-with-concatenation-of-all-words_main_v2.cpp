int main() {
    vector<Test> tests = {
        {"barfoothefoobarman", {"foo", "bar"}},
        {"wordgoodgoodgoodbestword", {"word", "good", "best", "word"}},
        {"barfoofoobarthefoobarman", {"bar", "foo", "the"}},
        {"lingmindraboofooowingdingbarrwingmonkeypoundcake", {"fooo", "barr", "wing", "ding", "wing"}},
        {"aaaaaa", {"aa", "aa", "aa"}},
        {"abababab", {"ab", "ba", "ab"}},
        {"abcabcabc", {"a", "b", "c"}},
        {"catcatdogcatdog", {"cat", "dog", "cat"}},
        {"short", {"longg", "words"}},
        {"foobarfoobar", {"foo", "bar", "foo"}}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<int> r = sol.findSubstring(t.s, const_cast<vector<string>&>(t.words));
            checksum += static_cast<int>(r.size());
        }
        sink = checksum;
    }

    return 0;
}