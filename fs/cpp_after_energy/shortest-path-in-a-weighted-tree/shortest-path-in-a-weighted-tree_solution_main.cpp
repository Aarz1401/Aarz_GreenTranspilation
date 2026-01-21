int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestInput> tests;
    tests.reserve(10);

    // Test 1: Small 2-node tree with multiple updates/queries
    {
        TestInput t;
        t.n = 2;
        t.edges = { {1, 2, 5} };
        t.queries = {
            {2, 1}, {2, 2},
            {1, 1, 2, 7}, {2, 2},
            {1, 1, 2, 3}, {2, 2}
        };
        tests.push_back(std::move(t));
    }

    // Test 2: Chain of 5 nodes
    {
        TestInput t;
        t.n = 5;
        for (int i = 1; i < t.n; ++i) {
            t.edges.push_back({i, i + 1, i}); // weights 1,2,3,4
        }
        t.queries = {
            {2, 5},
            {1, 2, 3, 10},
            {2, 5},
            {1, 4, 5, 1},
            {2, 3},
            {1, 1, 2, 5},
            {2, 5},
            {2, 1},
            {2, 4}
        };
        tests.push_back(std::move(t));
    }

    // Test 3: Star tree centered at 1
    {
        TestInput t;
        t.n = 7;
        for (int v = 2; v <= 7; ++v) {
            t.edges.push_back({1, v, 2 * (v - 1)}); // 2,4,6,8,10,12
        }
        t.queries = {
            {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7},
            {1, 1, 7, 3}, {2, 7},
            {1, 1, 2, 5}, {2, 2},
            {1, 1, 6, 1}, {2, 6},
            {2, 1}
        };
        tests.push_back(std::move(t));
    }

    // Test 4: Balanced binary tree with updates
    {
        TestInput t;
        t.n = 7;
        t.edges = {
            {1, 2, 3}, {1, 3, 5},
            {2, 4, 2}, {2, 5, 4},
            {3, 6, 6}, {3, 7, 8}
        };
        t.queries = {
            {2, 4}, {2, 5}, {2, 6}, {2, 7},
            {1, 2, 5, 10},
            {1, 1, 3, 7},
            {2, 5}, {2, 6}, {2, 7}
        };
        tests.push_back(std::move(t));
    }

    // Test 5: Deep chain with large weights
    {
        TestInput t;
        t.n = 10;
        for (int i = 1; i < t.n; ++i) {
            t.edges.push_back({i, i + 1, 100000 + i});
        }
        t.queries = {
            {2, 10},
            {1, 5, 6, 200000},
            {2, 10},
            {1, 1, 2, 50000},
            {2, 2}, {2, 10}
        };
        tests.push_back(std::move(t));
    }

    // Test 6: 1-indexed heap-like tree (n=15) with patterned weights
    {
        TestInput t;
        t.n = 15;
        for (int i = 2; i <= t.n; ++i) {
            int p = i / 2;
            int w = (i * 3) % 10 + 1;
            t.edges.push_back({p, i, w});
        }
        t.queries = {
            {2, 15}, {2, 8},
            {1, 7, 14, 9}, {2, 14},
            {1, 5, 10, 8}, {2, 10},
            {1, 1, 3, 5}, {2, 6}, {2, 15},
            {1, 2, 5, 7}, {2, 9}, {2, 12}
        };
        tests.push_back(std::move(t));
    }

    // Test 7: Mixed shape with repeated edge updates
    {
        TestInput t;
        t.n = 8;
        t.edges = {
            {1, 2, 1}, {1, 3, 2},
            {2, 4, 3}, {2, 5, 4},
            {3, 6, 5}, {6, 7, 6}, {6, 8, 7}
        };
        t.queries = {
            {2, 7},
            {1, 6, 7, 1}, {2, 7},
            {1, 6, 7, 10}, {2, 7},
            {1, 3, 6, 1},
            {2, 8}, {2, 5}
        };
        tests.push_back(std::move(t));
    }

    // Test 8: Star with only queries (no updates)
    {
        TestInput t;
        t.n = 5;
        t.edges = {
            {1, 2, 1}, {1, 3, 2}, {1, 4, 3}, {1, 5, 4}
        };
        t.queries = {
            {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}
        };
        tests.push_back(std::move(t));
    }

    // Test 9: Chain with all updates before queries
    {
        TestInput t;
        t.n = 6;
        t.edges = {
            {1, 2, 5}, {2, 3, 5}, {3, 4, 5}, {4, 5, 5}, {5, 6, 5}
        };
        t.queries = {
            {1, 2, 3, 1}, {1, 4, 5, 2}, {1, 1, 2, 3}, {1, 5, 6, 4}, {1, 3, 4, 5},
            {2, 6}, {2, 3}, {2, 5}, {2, 1}, {2, 2}
        };
        tests.push_back(std::move(t));
    }

    // Test 10: Random-ish tree with mixed queries/updates
    {
        TestInput t;
        t.n = 12;
        t.edges = {
            {1, 2, 3}, {1, 3, 1},
            {2, 4, 4}, {2, 5, 2},
            {3, 6, 7}, {3, 7, 5},
            {4, 8, 6}, {5, 9, 3},
            {6, 10, 2}, {7, 11, 4}, {7, 12, 8}
        };
        t.queries = {
            {2, 12}, {2, 11}, {2, 8},
            {1, 7, 12, 3}, {2, 12},
            {1, 1, 3, 2}, {1, 2, 5, 6},
            {2, 9}, {2, 3}, {2, 10}, {2, 5},
            {1, 6, 10, 5}, {2, 10},
            {1, 4, 8, 1}, {2, 8},
            {2, 1}
        };
        tests.push_back(std::move(t));
    }

    Solution solver;

    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            vector<int> res = solver.treeQueries(t.n, t.edges, t.queries);
            for (int v : res) {
                checksum += static_cast<unsigned long long>(v) * 1315423911ULL + static_cast<unsigned long long>(iter);
            }
            checksum += static_cast<unsigned long long>(res.size());
        }
    }
    auto end = chrono::high_resolution_clock::now();

    double elapsed_ms = chrono::duration<double, std::milli>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}