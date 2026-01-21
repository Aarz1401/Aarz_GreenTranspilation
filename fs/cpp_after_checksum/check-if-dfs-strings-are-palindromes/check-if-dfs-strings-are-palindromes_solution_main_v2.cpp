int main() {
    vector<TestCase> tests = {
        { {-1}, "z" },
        { {-1, 0, 1, 2, 3}, "abcba" },
        { {-1, 0, 0, 0, 0, 0}, "abccba" },
        { {-1, 0, 0, 1, 1, 2, 2}, "abacaba" },
        { {-1, 0, 0, 1, 1, 3, 3, 2}, "abcdedcb" },
        { {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8}, "aaaaabaaaa" },
        { {-1, 0, 0, 0, 1, 1, 2, 3, 3, 6, 8, 8}, "abcddcbaabca" },
        { {-1, 0, 0, 0, 1, 3, 3, 6, 6}, "racecarzz" },
        { {-1, 0}, "ab" },
        { {-1, 0, 0, 1, 3, 3, 2, 2, 2, 8, 8}, "zzxyxxyxxzz" }
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            vector<bool> ans = sol.findAnswer(const_cast<vector<int>&>(tc.parent), tc.s);
            for (bool b : ans) checksum += b;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}