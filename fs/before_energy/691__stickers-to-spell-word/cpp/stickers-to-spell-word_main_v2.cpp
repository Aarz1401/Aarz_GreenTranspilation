int main() {
    vector<TestCase> tests;
    tests.reserve(10);
    tests.push_back({{"with","example","science"}, "thehat"});
    tests.push_back({{"notice","possible"}, "basicbasic"});
    tests.push_back({{"these","guess","about","garden","him"}, "atomher"});
    tests.push_back({{"travel","broadcast","player","game"}, "goal"});
    tests.push_back({{"aaaa","bbbb","cc","dd"}, "abcd"});
    tests.push_back({{"ab","bc","cd"}, "abcd"});
    tests.push_back({{"ab","ab","ab"}, "aabb"});
    tests.push_back({{"hello","world","leetcode"}, "hold"});
    tests.push_back({{"abc","abd","cde","def"}, "feed"});
    tests.push_back({{"letter","collection","stickers","random","words","for","testing"}, "score"});

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            int res = sol.minStickers(const_cast<vector<string>&>(tc.stickers), tc.target);
            checksum += res;
        }
        sink = checksum;
    }

    return 0;
}