int main() {
    // Prepare 10 diverse test cases
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) n = 0 (empty graph)
    tests.push_back(TestCase{
        0,
        {},
        {}
    });

    // 2) Single node, positive score
    tests.push_back(TestCase{
        1,
        {},
        {5}
    });

    // 3) Two nodes with dependency 0 -> 1
    tests.push_back(TestCase{
        2,
        {{0, 1}},
        {3, 4}
    });

    // 4) Three nodes, no dependencies, mix of negative and positive scores
    tests.push_back(TestCase{
        3,
        {},
        {-1, 2, 1}
    });

    // 5) Star dependencies: 0 prerequisite for 1,2,3
    tests.push_back(TestCase{
        4,
        {{0,1}, {0,2}, {0,3}},
        {10, -5, 3, 2}
    });

    // 6) Chain 0 -> 1 -> 2 -> 3 -> 4
    tests.push_back(TestCase{
        5,
        {{0,1}, {1,2}, {2,3}, {3,4}},
        {1, -2, 3, -4, 5}
    });

    // 7) Random small DAG
    tests.push_back(TestCase{
        6,
        {{0,2}, {1,2}, {2,3}, {1,4}, {4,5}},
        {7, -3, 5, -2, 4, 1}
    });

    // 8) Dense layered DAG: each j depends on all i < j (unique topological order)
    {
        int n = 8;
        vector<vector<int>> edges8;
        for (int j = 1; j < n; ++j) {
            for (int i = 0; i < j; ++i) {
                edges8.push_back({i, j});
            }
        }
        vector<int> score8 = {1, 2, 3, 4, 5, 6, 7, 8};
        tests.push_back(TestCase{n, edges8, score8});
    }

    // 9) Two disconnected chains
    tests.push_back(TestCase{
        10,
        {{0,1}, {1,2}, {2,3}, {4,5}, {5,6}, {6,7}, {7,8}, {8,9}},
        {9, -1, 8, -2, 7, -3, 6, -4, 5, -5}
    });

    // 10) Larger DAG with mixed dependencies
    tests.push_back(TestCase{
        12,
        {
            {0,3}, {1,3}, {1,4}, {2,5}, {3,6}, {4,6}, {5,7}, {6,8}, {2,8},
            {7,9}, {8,10}, {9,11}
        },
        {3, -6, 7, 2, -1, 4, -3, 5, -2, 8, -4, 6}
    });

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.maxProfit(tc.n, tc.edges, tc.score);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}