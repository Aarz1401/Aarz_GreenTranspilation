int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) n=1, complete
    tests.push_back({1, build_complete_edges(1), string("a")});

    // 2) n=5, complete
    tests.push_back({5, build_complete_edges(5), string("abcde")});

    // 3) n=6, complete
    tests.push_back({6, build_complete_edges(6), string("aabbcc")});

    // 4) n=12, complete
    tests.push_back({12, build_complete_edges(12), string("abacabadabac")});

    // 5) n=7, almost complete (missing one edge)
    tests.push_back({7, build_almost_complete_edges(7, 1, 5), string("abacaba")});

    // 6) n=9, path
    {
        vector<vector<int>> e;
        for (int i = 0; i < 8; ++i) e.push_back({i, i + 1});
        tests.push_back({9, e, string("abccbaabc")});
    }

    // 7) n=9, star centered at 0
    {
        vector<vector<int>> e;
        for (int i = 1; i < 9; ++i) e.push_back({0, i});
        tests.push_back({9, e, string("aaaaaaaaa")});
    }

    // 8) n=7, cycle
    {
        vector<vector<int>> e;
        for (int i = 0; i < 6; ++i) e.push_back({i, i + 1});
        e.push_back({6, 0});
        tests.push_back({7, e, string("abcdefa")});
    }

    // 9) n=10, tree
    {
        vector<vector<int>> e = {
            {0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{4,8},{6,9}
        };
        tests.push_back({10, e, string("abcabcabca")});
    }

    // 10) n=8, two components (two paths)
    {
        vector<vector<int>> e = {
            {0,1},{1,2},{2,3},
            {4,5},{5,6},{6,7}
        };
        tests.push_back({8, e, string("abbaabba")});
    }

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            int res = sol.maxLen(t.n, const_cast<vector<vector<int>>&>(t.edges), t.label);
            checksum += res;
        }
        sink = checksum;
    }

    return 0;
}