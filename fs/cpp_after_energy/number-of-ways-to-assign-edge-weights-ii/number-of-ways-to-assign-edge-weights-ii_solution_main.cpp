int main() {
    // Prepare 10 diverse test cases
    vector<Test> tests;

    // 1) Single node tree, self queries
    {
        Test t;
        t.edges = {}; // n = 1
        t.queries = {{1,1}, {1,1}, {1,1}};
        tests.push_back(t);
    }

    // 2) Two-node tree with various pairs
    {
        Test t;
        t.edges = {{1,2}};
        t.queries = {{1,2}, {2,1}, {1,1}, {2,2}, {1,2}};
        tests.push_back(t);
    }

    // 3) Chain of 5 nodes
    {
        Test t;
        t.edges = {{1,2},{2,3},{3,4},{4,5}};
        t.queries = {{1,5}, {2,4}, {3,5}, {1,3}, {2,5}};
        tests.push_back(t);
    }

    // 4) Star with 6 nodes centered at 1
    {
        Test t;
        t.edges = {{1,2},{1,3},{1,4},{1,5},{1,6}};
        t.queries = {{2,3}, {4,6}, {2,5}, {1,3}, {5,5}};
        tests.push_back(t);
    }

    // 5) Balanced-ish binary tree with 7 nodes
    {
        Test t;
        t.edges = {{1,2},{1,3},{2,4},{2,5},{3,6},{3,7}};
        t.queries = {{4,5}, {4,6}, {2,3}, {7,7}, {5,6}, {1,7}, {4,7}};
        tests.push_back(t);
    }

    // 6) Unbalanced tree with 10 nodes
    {
        Test t;
        t.edges = {{1,2},{2,3},{3,4},{4,5},{5,6},{3,7},{7,8},{2,9},{9,10}};
        t.queries = {{1,6}, {8,10}, {4,7}, {2,8}, {6,9}, {1,10}, {5,5}};
        tests.push_back(t);
    }

    // 7) Long chain with 15 nodes
    {
        Test t;
        for (int i = 1; i < 15; ++i) t.edges.push_back({i, i+1});
        t.queries = {{1,15}, {1,8}, {7,14}, {3,12}, {5,5}, {2,13}, {4,11}};
        tests.push_back(t);
    }

    // 8) Tree with 4 nodes but empty queries
    {
        Test t;
        t.edges = {{1,2},{2,3},{2,4}};
        t.queries = {};
        tests.push_back(t);
    }

    // 9) Multi-level tree with 8 nodes
    {
        Test t;
        t.edges = {{1,2},{1,3},{2,4},{2,5},{3,6},{6,7},{6,8}};
        t.queries = {{4,5}, {4,6}, {7,8}, {3,5}, {2,8}, {1,7}, {5,7}};
        tests.push_back(t);
    }

    // 10) Larger tree with 20 nodes
    {
        Test t;
        t.edges = {
            {1,2},{1,3},{2,4},{2,5},{3,6},{3,7},
            {4,8},{5,9},{5,10},{6,11},{7,12},{7,13},
            {8,14},{9,15},{10,16},{11,17},{12,18},{13,19},{14,20}
        };
        t.queries = {
            {14,20}, {15,16}, {17,18}, {19,4}, {10,12}, {2,20}, {6,13}, {1,11}, {3,15}, {8,18}
        };
        tests.push_back(t);
    }

    // Benchmark
    using namespace std::chrono;
    int64_t checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            Solution sol;
            vector<vector<int>> edges = t.edges;
            vector<vector<int>> queries = t.queries;
            vector<int> ans = sol.assignEdgeWeights(edges, queries);
            checksum += static_cast<int64_t>(ans.size());
            for (size_t i = 0; i < ans.size(); ++i) {
                checksum += ans[i];
                checksum ^= (checksum << 7) ^ (checksum >> 3); // mix a bit
            }
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}