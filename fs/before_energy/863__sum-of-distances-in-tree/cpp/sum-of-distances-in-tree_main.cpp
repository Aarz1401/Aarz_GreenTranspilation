int main() {
    vector<TestCase> tests;

    // 1) Single node
    {
        TestCase tc;
        tc.N = 1;
        tc.edges = {};
        tests.push_back(move(tc));
    }

    // 2) Two nodes
    {
        TestCase tc;
        tc.N = 2;
        tc.edges = {{0, 1}};
        tests.push_back(move(tc));
    }

    // 3) Chain of 10
    {
        TestCase tc;
        tc.N = 10;
        for (int i = 0; i < tc.N - 1; ++i) tc.edges.push_back({i, i + 1});
        tests.push_back(move(tc));
    }

    // 4) Star of 10 centered at 0
    {
        TestCase tc;
        tc.N = 10;
        for (int i = 1; i < tc.N; ++i) tc.edges.push_back({0, i});
        tests.push_back(move(tc));
    }

    // 5) Balanced binary tree of 15 nodes (0-indexed heap)
    {
        TestCase tc;
        tc.N = 15;
        for (int i = 0; 2 * i + 1 < tc.N; ++i) {
            tc.edges.push_back({i, 2 * i + 1});
            if (2 * i + 2 < tc.N) tc.edges.push_back({i, 2 * i + 2});
        }
        tests.push_back(move(tc));
    }

    // 6) Deterministic pseudo-random tree of 20 nodes
    {
        TestCase tc;
        tc.N = 20;
        for (int i = 1; i < tc.N; ++i) {
            int p = (i * 7 + 3) % i;
            tc.edges.push_back({p, i});
        }
        tests.push_back(move(tc));
    }

    // 7) Double-star structure with two hubs connected
    {
        TestCase tc;
        tc.N = 12;
        // hub A = 0 with children 1..5
        for (int i = 1; i <= 5; ++i) tc.edges.push_back({0, i});
        // hub B = 6 with children 7..11
        for (int i = 7; i <= 11; ++i) tc.edges.push_back({6, i});
        // connect hubs
        tc.edges.push_back({0, 6});
        tests.push_back(move(tc));
    }

    // 8) Root with multiple chains of varying lengths
    {
        TestCase tc;
        tc.N = 15;
        // root connections
        for (int i = 1; i <= 5; ++i) tc.edges.push_back({0, i});
        // chains
        tc.edges.push_back({1, 6});               // length 1
        tc.edges.push_back({2, 7}); tc.edges.push_back({7, 8}); // length 2
        tc.edges.push_back({3, 9}); tc.edges.push_back({9, 10}); tc.edges.push_back({10, 11}); // length 3
        tc.edges.push_back({4, 12});              // length 1
        tc.edges.push_back({5, 13}); tc.edges.push_back({13, 14}); // length 2
        tests.push_back(move(tc));
    }

    // 9) Long chain with small side branches
    {
        TestCase tc;
        tc.N = 25;
        for (int i = 0; i < 19; ++i) tc.edges.push_back({i, i + 1}); // chain 0..19
        tc.edges.push_back({10, 20});
        tc.edges.push_back({10, 21});
        tc.edges.push_back({15, 22});
        tc.edges.push_back({18, 23});
        tc.edges.push_back({18, 24});
        tests.push_back(move(tc));
    }

    // 10) Larger deterministic tree of 100 nodes
    {
        TestCase tc;
        tc.N = 100;
        for (int i = 1; i < tc.N; ++i) {
            int p = (i * i + 31) % i;
            tc.edges.push_back({p, i});
        }
        tests.push_back(move(tc));
    }

    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        Solution sol;
        for (const auto& tc : tests) {
            vector<vector<int>> edges = tc.edges; // pass by non-const ref per signature
            vector<int> result = sol.sumOfDistancesInTree(tc.N, edges);
            long long local = 0;
            for (int v : result) local += v;
            checksum += local + iter; // tie to iter to ensure work isn't optimized away
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
    cout << "Checksum: " << static_cast<long long>(checksum) << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}