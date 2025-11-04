int main() {
    // Define 10 diverse test inputs
    vector<vector<vector<int>>> tests;

    // 1) Pure cycle
    tests.push_back({{1,2},{2,3},{3,1}});

    // 2) Two parents, no cycle
    tests.push_back({{1,2},{1,3},{2,3}});

    // 3) Two parents + cycle
    tests.push_back({{2,1},{3,1},{4,2},{1,4}});

    // 4) Larger cycle
    tests.push_back({{1,2},{2,3},{3,4},{4,5},{5,3}});

    // 5) Two parents, no cycle in union pass
    tests.push_back({{1,2},{2,3},{3,4},{1,4},{4,5}});

    // 6) Back edge to root creates cycle
    tests.push_back({{1,2},{1,3},{2,4},{3,5},{5,1}});

    // 7) Larger, two parents, no cycle
    tests.push_back({{1,2},{1,3},{2,4},{3,5},{4,6},{5,6}});

    // 8) Two parents + existing cycle elsewhere
    tests.push_back({{1,2},{2,3},{3,1},{4,3},{3,5},{5,6}});

    // 9) Minimal n=2 forming cycle
    tests.push_back({{1,2},{2,1}});

    // 10) Two parents + cycle (choose earlier parent)
    tests.push_back({{1,2},{2,3},{3,4},{4,1},{1,5},{5,3}});

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto edges : tests) {
            vector<int> res = sol.findRedundantDirectedConnection(edges);
            for (int v : res) {
                checksum += v + (iter & 1); // simple mix to avoid optimization
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}