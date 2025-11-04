int main() {
    // Prepare 10 diverse test cases
    vector<vector<vector<int>>> allRoutes;
    vector<pair<int, int>> ST;

    // Test 1: Basic example - expect 2
    allRoutes.push_back({{1, 2, 7}, {3, 6, 7}});
    ST.emplace_back(1, 6);

    // Test 2: S == T - expect 0
    allRoutes.push_back({{1, 5, 9}});
    ST.emplace_back(5, 5);

    // Test 3: Unreachable target - expect -1
    allRoutes.push_back({{1, 2, 3}, {4, 5, 6}});
    ST.emplace_back(1, 6);

    // Test 4: Direct bus available - expect 1
    allRoutes.push_back({{10, 20, 30}, {5, 15}});
    ST.emplace_back(20, 30);

    // Test 5: Multiple transfers needed - expect 4
    allRoutes.push_back({{1, 5, 9}, {9, 10}, {10, 15}, {15, 20}});
    ST.emplace_back(1, 20);

    // Test 6: Large stop IDs - expect 4
    allRoutes.push_back({{1000000, 2000000}, {2000000, 3000000}, {3000000, 4000000, 5000000}, {5000000, 6000000}, {7000000}});
    ST.emplace_back(1000000, 6000000);

    // Test 7: Branching paths - expect minimal transfers (likely 4)
    allRoutes.push_back({{1, 2, 3, 4}, {4, 5, 6}, {2, 7}, {7, 8, 9}, {9, 10}});
    ST.emplace_back(1, 10);

    // Test 8: Single large route - expect 1
    {
        vector<int> bigRoute;
        for (int i = 0; i < 200; ++i) bigRoute.push_back(i);
        allRoutes.push_back({bigRoute});
        ST.emplace_back(0, 199);
    }

    // Test 9: No routes - expect -1
    allRoutes.push_back({});
    ST.emplace_back(1, 2);

    // Test 10: Overlapping routes with immediate reach - likely 1
    allRoutes.push_back({{1, 1, 1, 2}, {2, 3, 3, 4}, {4, 5}, {1, 6}, {6, 7, 8, 9, 10}});
    ST.emplace_back(1, 10);

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < allRoutes.size(); ++i) {
            // Make a copy of routes for each call to avoid any accidental state across runs
            vector<vector<int>> routes = allRoutes[i];
            int S = ST[i].first;
            int T = ST[i].second;
            int res = sol.numBusesToDestination(routes, S, T);
            checksum += res;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}