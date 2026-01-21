int main() {
    vector<Test> tests;

    // Test 1: Single node
    tests.push_back({
        {}, // edges
        {5} // nums
    });

    // Test 2: Two nodes, simple edge
    tests.push_back({
        {{0, 1, 3}},
        {1, 2}
    });

    // Test 3: Three nodes, star centered at 0
    tests.push_back({
        {{0, 1, 4}, {0, 2, 7}},
        {2, 3, 1}
    });

    // Test 4: Four nodes in a path, unit weights
    tests.push_back({
        {{0, 1, 1}, {1, 2, 1}, {2, 3, 1}},
        {1, 2, 3, 4}
    });

    // Test 5: Five nodes, include zero-weight edge
    tests.push_back({
        {{0, 1, 0}, {1, 2, 5}, {1, 3, 2}, {3, 4, 3}},
        {5, 4, 5, 6, 7}
    });

    // Test 6: Six nodes, balanced branching
    tests.push_back({
        {{0, 1, 2}, {0, 2, 3}, {1, 3, 4}, {1, 4, 1}, {2, 5, 6}},
        {3, 4, 5, 6, 4, 5}
    });

    // Test 7: Seven nodes, mixed large weights
    tests.push_back({
        {{0, 1, 10}, {1, 2, 20}, {2, 3, 30}, {1, 4, 40}, {4, 5, 50}, {4, 6, 60}},
        {7, 6, 5, 4, 3, 2, 1}
    });

    // Test 8: Eight nodes, multiple zero-weight edges
    tests.push_back({
        {{0, 1, 0}, {0, 2, 0}, {1, 3, 1}, {1, 4, 0}, {2, 5, 2}, {2, 6, 0}, {6, 7, 3}},
        {1, 1, 2, 3, 3, 4, 5, 6}
    });

    // Test 9: Nine nodes, heavier weights
    tests.push_back({
        {{0, 1, 1000}, {0, 2, 2000}, {1, 3, 1500}, {1, 4, 500}, {2, 5, 2500}, {2, 6, 3500}, {6, 7, 4500}, {6, 8, 5500}},
        {10, 11, 12, 13, 9, 8, 7, 6, 5}
    });

    // Test 10: Ten nodes, varied structure
    tests.push_back({
        {{0, 1, 5}, {0, 2, 3}, {1, 3, 2}, {1, 4, 4}, {2, 5, 6}, {2, 6, 1}, {5, 7, 2}, {6, 8, 3}, {8, 9, 4}},
        {2, 3, 4, 5, 3, 4, 5, 6, 7, 8}
    });

    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            auto res = sol.longestSpecialPath(t.edges, t.nums);
            checksum += res[0];
            checksum ^= (res[1] << 1);
        }
        sink = checksum;
    }

    return 0;
}