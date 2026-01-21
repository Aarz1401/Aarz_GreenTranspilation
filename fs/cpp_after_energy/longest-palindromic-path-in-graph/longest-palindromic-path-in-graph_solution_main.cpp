int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    // 1) n=1, complete (trivial)
    tests.push_back(TestCase{
        1,
        build_complete_edges(1),
        "a"
    });

    // 2) n=2, complete
    tests.push_back(TestCase{
        2,
        build_complete_edges(2),
        "aa"
    });

    // 3) n=3, complete
    tests.push_back(TestCase{
        3,
        build_complete_edges(3),
        "abc"
    });

    // 4) n=4, path graph
    {
        vector<vector<int>> e = {{0,1},{1,2},{2,3}};
        tests.push_back(TestCase{
            4,
            e,
            "abba"
        });
    }

    // 5) n=6, star graph
    {
        int n = 6;
        vector<vector<int>> e;
        for (int i = 1; i < n; ++i) e.push_back({0, i});
        tests.push_back(TestCase{
            n,
            e,
            "abccba"
        });
    }

    // 6) n=8, complete
    tests.push_back(TestCase{
        8,
        build_complete_edges(8),
        "aabbccdd"
    });

    // 7) n=9, complete
    tests.push_back(TestCase{
        9,
        build_complete_edges(9),
        "aaabbbccc"
    });

    // 8) n=10, almost complete (missing one edge)
    tests.push_back(TestCase{
        10,
        build_almost_complete_edges(10, 2, 7),
        "abcabcabca"
    });

    // 9) n=12, complete
    tests.push_back(TestCase{
        12,
        build_complete_edges(12),
        "aaaabbbbcccc"
    });

    // 10) n=14, complete
    tests.push_back(TestCase{
        14,
        build_complete_edges(14),
        "aabbccddeeffgg"
    });

    Solution sol;
    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.maxLen(tc.n, tc.edges, tc.label);
        }
    }

    auto end = high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_ms = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms.count() << "\n";

    return 0;
}
