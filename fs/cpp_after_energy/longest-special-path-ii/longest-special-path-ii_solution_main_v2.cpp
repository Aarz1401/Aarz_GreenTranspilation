int main() {
    vector<Test> tests;

    // Test 1: Single node
    tests.push_back(Test{
        {}, {5}
    });

    // Test 2: Two nodes, single edge
    tests.push_back(Test{
        {{0,1,7}}, {1,1}
    });

    // Test 3: Path of 5 nodes
    tests.push_back(Test{
        {{0,1,3},{1,2,4},{2,3,5},{3,4,6}},
        {2,1,2,3,1}
    });

    // Test 4: Star with center 0
    tests.push_back(Test{
        {{0,1,10},{0,2,20},{0,3,30},{0,4,40},{0,5,50}},
        {1,2,3,2,1,3}
    });

    // Test 5: Balanced binary tree (7 nodes)
    tests.push_back(Test{
        {{0,1,2},{0,2,3},{1,3,4},{1,4,5},{2,5,6},{2,6,7}},
        {3,1,2,3,1,2,3}
    });

    // Test 6: Random tree (8 nodes)
    tests.push_back(Test{
        {{0,1,5},{1,2,1},{1,3,9},{3,4,2},{3,5,8},{5,6,7},{2,7,4}},
        {4,4,2,5,1,3,2,5}
    });

    // Test 7: Tree (10 nodes)
    tests.push_back(Test{
        {{0,1,3},{0,2,4},{1,3,2},{1,4,6},{2,5,5},{2,6,1},{6,7,7},{4,8,9},{8,9,3}},
        {1,3,5,7,9,2,4,6,8,10}
    });

    // Test 8: Larger tree (20 nodes)
    tests.push_back(Test{
        {
            {0,1,1},{0,2,2},{1,3,3},{1,4,4},{2,5,5},{2,6,6},
            {3,7,7},{3,8,8},{4,9,9},{4,10,10},{5,11,11},{5,12,12},
            {6,13,13},{6,14,14},{7,15,15},{8,16,16},{9,17,17},
            {10,18,18},{11,19,19}
        },
        {1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2}
    });

    // Test 9: Star (15 nodes)
    {
        vector<vector<int>> e9;
        for (int v = 1; v <= 14; ++v) e9.push_back({0, v, 2 * v});
        tests.push_back(Test{
            e9,
            {5,5,5,4,4,4,3,3,3,2,2,2,1,1,1}
        });
    }

    // Test 10: Larger tree (30 nodes)
    tests.push_back(Test{
        {
            {0,1,1},{0,2,2},{1,3,3},{1,4,4},{2,5,5},{2,6,6},
            {3,7,7},{3,8,8},{4,9,9},{4,10,10},{5,11,11},{5,12,12},
            {6,13,13},{6,14,14},{7,15,15},{7,16,16},{8,17,17},{8,18,18},
            {9,19,19},{9,20,20},{10,21,21},{10,22,22},{11,23,23},{12,24,24},
            {13,25,25},{14,26,26},{15,27,27},{16,28,28},{17,29,29}
        },
        {1,2,3,4,5,6,7,8,9,10, 1,2,3,4,5,6,7,8,9,10, 10,9,8,7,6,5,4,3,2,1}
    });

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (int t = 0; t < 10; ++t) {
            vector<int> res = sol.longestSpecialPath(tests[t].edges, tests[t].nums);
            if (res.size() >= 2) checksum += res[0] + res[1];
        }
        sink = checksum;
    }

    return 0;
}