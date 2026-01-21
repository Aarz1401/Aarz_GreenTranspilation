int main() {
    // Define 10 diverse test inputs
    vector<vector<int>> nums_list;
    vector<vector<vector<int>>> edges_list;

    // Test 1: Single node
    nums_list.push_back({1});
    edges_list.push_back({});

    // Test 2: Two nodes
    nums_list.push_back({1, 2});
    edges_list.push_back({{0, 1, 5}});

    // Test 3: Three-node chain
    nums_list.push_back({2, 1, 2});
    edges_list.push_back({{0, 1, 3}, {1, 2, 4}});

    // Test 4: Star centered at 0
    nums_list.push_back({1, 1, 2, 2, 3});
    edges_list.push_back({{0, 1, 1}, {0, 2, 2}, {0, 3, 3}, {0, 4, 4}});

    // Test 5: Balanced tree with varied weights
    nums_list.push_back({3, 1, 4, 1, 5, 9, 2});
    edges_list.push_back({{0, 1, 2}, {0, 2, 3}, {1, 3, 4}, {1, 4, 5}, {2, 5, 6}, {2, 6, 7}});

    // Test 6: Random-ish tree, Fibonacci-like nums
    nums_list.push_back({7, 1, 1, 2, 3, 5, 8, 13});
    edges_list.push_back({{0, 1, 10}, {1, 2, 20}, {1, 3, 5}, {3, 4, 8}, {0, 5, 7}, {5, 6, 3}, {6, 7, 12}});

    // Test 7: Chain of 10 nodes with patterned nums
    nums_list.push_back({0, 0, 1, 1, 0, 2, 2, 3, 3, 0});
    {
        vector<vector<int>> e;
        for (int k = 1; k < 10; ++k) {
            e.push_back({k - 1, k, k * 2 + 1});
        }
        edges_list.push_back(e);
    }

    // Test 8: Deeper tree with negatives and large nums
    nums_list.push_back({5, 4, 3, 2, 1, 0, -1, -2, -3, 100, 100, 100});
    edges_list.push_back({{0, 1, 1}, {0, 2, 2}, {2, 3, 3}, {2, 4, 4}, {4, 5, 5},
                          {1, 6, 6}, {6, 7, 7}, {6, 8, 8}, {8, 9, 9}, {9, 10, 10}, {10, 11, 11}});

    // Test 9: Binary tree of 15 nodes
    {
        vector<int> nums9;
        for (int x = 0; x < 15; ++x) nums9.push_back(x % 5);
        nums_list.push_back(nums9);

        vector<vector<int>> e9;
        for (int node = 1; node < 15; ++node) {
            int parent = (node - 1) / 2;
            e9.push_back({parent, node, node + 1});
        }
        edges_list.push_back(e9);
    }

    // Test 10: Multi-level branching
    nums_list.push_back({1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4});
    edges_list.push_back({
        {0, 1, 1}, {0, 2, 2}, {0, 3, 3}, {0, 4, 4}, {0, 5, 5},
        {5, 6, 6}, {5, 7, 7}, {5, 8, 8}, {5, 9, 9}, {5, 10, 10},
        {10, 11, 11}, {10, 12, 12}, {10, 13, 13},
        {13, 14, 14}, {14, 15, 15}, {14, 16, 16}, {14, 17, 17},
        {17, 18, 18}, {17, 19, 19}
    });

    // Benchmark
    Solution sol;
    uint64_t checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int t = 0; t < 10; ++t) {
            vector<vector<int>> edges = edges_list[t];
            vector<int> nums = nums_list[t];
            vector<int> res = sol.longestSpecialPath(edges, nums);
            checksum += (static_cast<uint64_t>(res[0]) * 1000003ULL) ^ (static_cast<uint64_t>(res[1]) + t);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> ms = end - start;
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << ms.count() << "\n";
    return 0;
}