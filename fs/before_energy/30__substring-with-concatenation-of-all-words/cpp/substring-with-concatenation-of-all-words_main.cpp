int main() {
    using namespace std;
    using namespace std::chrono;

    struct TestCase {
        string s;
        vector<string> words;
    };

    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Basic example with multiple matches
    tests.push_back({"barfoothefoobarman", {"foo", "bar"}});
    // 2) Repeated word counts
    tests.push_back({"wordgoodgoodgoodbestword", {"word", "good", "best", "good"}});
    // 3) All words identical, exact fit
    tests.push_back({"aaaaaa", {"aa", "aa", "aa"}});
    // 4) No match because one word not present
    tests.push_back({"abcabcabc", {"abc", "abd"}});
    // 5) Multiple overlapping matches
    tests.push_back({"catdogcatdog", {"cat", "dog"}});
    // 6) Shared prefixes "aaa"
    tests.push_back({"aaaaaa", {"aaa", "aaa"}});
    // 7) Mixed alphanumeric and uppercase
    tests.push_back({"A1B2A1B2A1", {"A1", "B2", "A1"}});
    // 8) Single-character words
    tests.push_back({"ababaabbababa", {"a", "b", "a"}});

    // 9) Larger input with repeated pattern
    {
        string s9;
        s9.reserve(12 * 60);
        for (int i = 0; i < 60; ++i) s9 += "barfoofoobar";
        tests.push_back({s9, {"foo", "bar"}});
    }

    // 10) Long words length 10 with multiple matches
    {
        string s10 = string("abcdefghij") + "klmnopqrst" + "abcdefghij" + "zzzzzzzzzz" + "klmnopqrst" + "abcdefghij" + "abcdefghij";
        tests.push_back({s10, {"abcdefghij", "klmnopqrst", "abcdefghij"}});
    }

    Solution sol;
    uint64_t checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<string> words = tc.words; // copy to match function signature (non-const)
            auto res = sol.findSubstring(tc.s, words);
            checksum += static_cast<uint64_t>(res.size());
            for (int idx : res) {
                checksum = checksum * 1315423911u + static_cast<uint64_t>(idx + 1);
            }
        }
    }

    auto end = high_resolution_clock::now();

    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}