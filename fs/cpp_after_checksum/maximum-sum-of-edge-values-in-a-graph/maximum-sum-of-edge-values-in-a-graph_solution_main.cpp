int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs (graphs)
    vector<pair<int, vector<vector<int>>>> tests;
    tests.reserve(10);

    // 1) Empty graph
    tests.push_back({0, {}});

    // 2) Single node, no edges
    tests.push_back({1, {}});

    // 3) Single edge (chain of length 2)
    tests.push_back({2, {{0,1}}});

    // 4) Triangle cycle (length 3)
    tests.push_back({3, {{0,1},{1,2},{2,0}}});

    // 5) Square with a tail (component not a cycle)
    tests.push_back({5, {{0,1},{1,2},{2,3},{3,0},{0,4}}});

    // 6) Two disjoint cycles: triangle and 4-cycle
    tests.push_back({7, {{0,1},{1,2},{2,0},{3,4},{4,5},{5,6},{6,3}}});

    // 7) Star graph centered at 0
    tests.push_back({6, {{0,1},{0,2},{0,3},{0,4},{0,5}}});

    // 8) Path of length 6
    tests.push_back({6, {{0,1},{1,2},{2,3},{3,4},{4,5}}});

    // 9) Mixed: chain of 3, cycle of 5, isolated node
    tests.push_back({9, {{0,1},{1,2}, {3,4},{4,5},{5,6},{6,7},{7,3}}});

    // 10) Larger mixed: 4-cycle, path of 5, path of 3
    tests.push_back({12, {
        {0,1},{1,2},{2,3},{3,0},        // 4-cycle
        {4,5},{5,6},{6,7},{7,8},        // path of 5 nodes
        {9,10},{10,11}                  // path of 3 nodes
    }});

    Solution sol;
    using clock_t = std::chrono::high_resolution_clock;

    unsigned long long checksum = 0;

    auto start = clock_t::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            int n = t.first;
            vector<vector<int>> edges = t.second; // make a local copy to match non-const ref signature
            checksum += static_cast<unsigned long long>(sol.maxScore(n, edges));
        }
    }

    auto end = clock_t::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}