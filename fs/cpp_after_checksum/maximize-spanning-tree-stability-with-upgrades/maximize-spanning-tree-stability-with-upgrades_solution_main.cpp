int main() {
    vector<TestCase> tests;

    // Test 1: All mandatory edges forming a spanning tree
    tests.push_back(TestCase{
        4,
        {
            {0, 1, 10, 1},
            {1, 2, 8, 1},
            {2, 3, 12, 1},
            {0, 2, 20, 0},
            {1, 3, 15, 0}
        },
        1
    });

    // Test 2: Mandatory edges form a cycle -> -1
    tests.push_back(TestCase{
        3,
        {
            {0, 1, 5, 1},
            {1, 2, 6, 1},
            {2, 0, 7, 1}
        },
        0
    });

    // Test 3: Mix of mandatory and optional, hitting both thresholds
    tests.push_back(TestCase{
        5,
        {
            {0, 1, 9, 1},
            {2, 3, 7, 1},
            {1, 2, 10, 0},
            {3, 4, 6, 0},
            {0, 4, 11, 0}
        },
        1
    });

    // Test 4: No mandatory edges, connected graph, k = 0
    tests.push_back(TestCase{
        5,
        {
            {0, 1, 4, 0},
            {1, 2, 9, 0},
            {2, 3, 3, 0},
            {3, 4, 8, 0},
            {0, 4, 5, 0},
            {1, 3, 7, 0},
            {0, 2, 6, 0}
        },
        0
    });

    // Test 5: Disconnected graph even with optional edges -> -1
    tests.push_back(TestCase{
        4,
        {
            {0, 1, 5, 0},
            {1, 2, 4, 0}
        },
        2
    });

    // Test 6: Larger graph with mix of edges and k = 2
    tests.push_back(TestCase{
        8,
        {
            {0, 1, 50, 1},
            {1, 2, 40, 1},
            {2, 3, 60, 1},
            {3, 4, 35, 0},
            {4, 5, 30, 0},
            {5, 6, 25, 0},
            {6, 7, 20, 0},
            {0, 2, 45, 0},
            {4, 7, 15, 0},
            {1, 3, 55, 0}
        },
        2
    });

    // Test 7: Redundant optionals and bridging edges, k = 2
    tests.push_back(TestCase{
        6,
        {
            {0, 1, 10, 1},
            {2, 3, 9, 1},
            {0, 2, 8, 0},
            {0, 1, 7, 0},
            {2, 3, 6, 0},
            {3, 4, 5, 0},
            {4, 5, 4, 0}
        },
        2
    });

    // Test 8: k >= n - 1, triggers only the 2*s branch at completion
    tests.push_back(TestCase{
        5,
        {
            {0, 1, 100, 0},
            {1, 2, 90, 0},
            {2, 3, 80, 0},
            {3, 4, 70, 0}
        },
        4
    });

    // Test 9: All optional edges with same strength
    tests.push_back(TestCase{
        4,
        {
            {0, 1, 5, 0},
            {1, 2, 5, 0},
            {2, 3, 5, 0},
            {0, 2, 5, 0},
            {1, 3, 5, 0}
        },
        1
    });

    // Test 10: Large strengths around 1e9, safe within int range after operations
    tests.push_back(TestCase{
        6,
        {
            {0, 1, 1000000000, 1},
            {2, 3, 1000000000, 1},
            {1, 2, 1000000000, 0},
            {3, 4, 1000000000, 0},
            {4, 5, 1000000000, 0}
        },
        0
    });

    Solution sol;

    auto start = high_resolution_clock::now();
    long long checksum = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<vector<int>> edgesCopy = tc.edges; // Copy since the solution sorts in place
            int res = sol.maxStability(tc.n, edgesCopy, tc.k);
            checksum += res;
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (us): " << elapsed_us << "\n";

    return 0;
}