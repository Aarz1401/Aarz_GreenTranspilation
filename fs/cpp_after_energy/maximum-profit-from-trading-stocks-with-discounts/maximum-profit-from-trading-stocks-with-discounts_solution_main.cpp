int main() {
    vector<TestCase> tests;

    // 1) Single node
    tests.push_back({
        1,
        {3},
        {9},
        {},
        3
    });

    // 2) Chain of 5
    {
        int n = 5;
        vector<vector<int>> h;
        for (int i = 1; i < n; ++i) h.push_back({i, i + 1});
        tests.push_back({
            n,
            {1, 2, 3, 4, 5},
            {2, 3, 7, 8, 12},
            h,
            7
        });
    }

    // 3) Star with 1 as root
    {
        int n = 7;
        vector<vector<int>> h;
        for (int i = 2; i <= n; ++i) h.push_back({1, i});
        tests.push_back({
            n,
            {2, 2, 3, 3, 4, 5, 1},
            {3, 5, 4, 6, 7, 7, 2},
            h,
            10
        });
    }

    // 4) Balanced binary tree (7 nodes)
    {
        int n = 7;
        vector<vector<int>> h = {
            {1,2},{1,3},{2,4},{2,5},{3,6},{3,7}
        };
        tests.push_back({
            n,
            {5,4,4,3,2,6,1},
            {9,7,5,5,4,7,4},
            h,
            12
        });
    }

    // 5) Random tree 10 nodes
    {
        int n = 10;
        vector<vector<int>> h = {
            {1,2},{1,3},{2,4},{2,5},{3,6},{3,7},{4,8},{5,9},{7,10}
        };
        tests.push_back({
            n,
            {3,6,2,5,8,4,7,3,6,5},
            {7,9,5,9,10,7,12,5,9,9},
            h,
            15
        });
    }

    // 6) Zero budget (should select none)
    {
        int n = 6;
        vector<vector<int>> h = { {1,2},{2,3},{3,4},{4,5},{5,6} };
        tests.push_back({
            n,
            {5,4,3,6,7,8},
            {6,5,5,8,9,10},
            h,
            0
        });
    }

    // 7) Zero profit everywhere (future == present)
    {
        int n = 5;
        vector<vector<int>> h = { {1,2},{2,3},{3,4},{4,5} };
        tests.push_back({
            n,
            {2,3,4,5,6},
            {2,3,4,5,6},
            h,
            20
        });
    }

    // 8) Negative profits (future < present)
    {
        int n = 4;
        vector<vector<int>> h = { {1,2},{1,3},{1,4} };
        tests.push_back({
            n,
            {5,6,7,8},
            {1,2,3,2},
            h,
            30
        });
    }

    // 9) High budget to take many
    {
        int n = 8;
        vector<vector<int>> h = { {1,2},{1,3},{2,4},{2,5},{3,6},{3,7},{6,8} };
        tests.push_back({
            n,
            {2,3,4,5,6,7,3,2},
            {6,7,8,9,10,12,6,4},
            h,
            100
        });
    }

    // 10) Medium tree 12 nodes mixed
    {
        int n = 12;
        vector<vector<int>> h = {
            {1,2},{1,3},{2,4},{2,5},{3,6},{3,7},{4,8},{4,9},{5,10},{7,11},{7,12}
        };
        tests.push_back({
            n,
            {4,7,3,6,5,8,2,3,4,6,5,7},
            {8,10,7,10,9,12,5,6,7,9,8,11},
            h,
            25
        });
    }

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            // Make copies as the function takes non-const references
            vector<int> p = tc.present;
            vector<int> f = tc.future;
            vector<vector<int>> h = tc.hierarchy;
            int res = sol.maxProfit(tc.n, p, f, h, tc.budget);
            checksum += res;
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed (ns): " << elapsed_ns << "\n";

    return 0;
}