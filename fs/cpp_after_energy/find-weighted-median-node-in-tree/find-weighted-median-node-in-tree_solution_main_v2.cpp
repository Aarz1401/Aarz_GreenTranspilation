int main() {
    vector<Test> tests;

    // 1) Single node
    tests.push_back({
        1,
        {},
        {{0,0}}
    });

    // 2) Two nodes
    tests.push_back({
        2,
        {{0,1,5}},
        {{0,1},{1,0},{0,0},{1,1}}
    });

    // 3) Three-node chain
    tests.push_back({
        3,
        {{0,1,2},{1,2,3}},
        {{0,2},{0,1},{1,2}}
    });

    // 4) Star with center 0
    tests.push_back({
        4,
        {{0,1,1},{0,2,2},{0,3,3}},
        {{1,2},{1,3},{2,3},{0,3}}
    });

    // 5) Chain with varied weights
    tests.push_back({
        5,
        {{0,1,1},{1,2,1},{2,3,10},{3,4,1}},
        {{0,4},{0,3},{2,4}}
    });

    // 6) Balanced-ish tree
    tests.push_back({
        6,
        {{0,1,4},{0,2,1},{1,3,2},{1,4,2},{2,5,7}},
        {{3,5},{4,5},{3,4},{2,5},{0,5}}
    });

    // 7) Unbalanced with a branch
    tests.push_back({
        7,
        {{0,1,1},{1,2,1},{2,3,1},{3,4,1},{4,5,10},{2,6,2}},
        {{6,5},{0,6},{1,4},{3,5}}
    });

    // 8) Larger branching
    tests.push_back({
        8,
        {{0,1,3},{0,2,5},{1,3,4},{1,4,6},{2,5,2},{5,6,1},{5,7,8}},
        {{3,7},{4,6},{6,7},{2,7}}
    });

    // 9) Long chain of 9
    tests.push_back({
        9,
        {{0,1,1},{1,2,1},{2,3,1},{3,4,1},{4,5,1},{5,6,1},{6,7,1},{7,8,1}},
        {{0,8},{2,6},{3,3},{1,7}}
    });

    // 10) Tree with varying weights
    tests.push_back({
        10,
        {{0,1,9},{0,2,3},{2,3,4},{2,4,5},{4,5,6},{4,6,7},{6,7,8},{6,8,2},{8,9,1}},
        {{1,9},{5,7},{3,5},{0,9},{2,6}}
    });

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<int> res = sol.findMedian(t.n, const_cast<vector<vector<int>>&>(t.edges), const_cast<vector<vector<int>>&>(t.queries));
            for (int x : res) checksum += x;
        }
        sink = checksum;
    }
    return 0;
}