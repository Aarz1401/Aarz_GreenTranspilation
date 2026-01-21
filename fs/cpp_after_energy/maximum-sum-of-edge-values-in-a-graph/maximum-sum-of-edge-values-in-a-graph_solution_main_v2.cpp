int main() {
    vector<Test> tests = {
        // 1) Single node, no edges
        {1, {}},
        // 2) Two nodes, one edge (path)
        {2, {{0,1}}},
        // 3) Triangle cycle
        {3, {{0,1},{1,2},{2,0}}},
        // 4) Square cycle
        {4, {{0,1},{1,2},{2,3},{3,0}}},
        // 5) Path of 4 nodes
        {4, {{0,1},{1,2},{2,3}}},
        // 6) Star with 5 nodes (center 0)
        {5, {{0,1},{0,2},{0,3},{0,4}}},
        // 7) Triangle + isolated node
        {4, {{0,1},{1,2},{2,0}}},
        // 8) 4-cycle + 3-node path
        {7, {{0,1},{1,2},{2,3},{3,0},{4,5},{5,6}}},
        // 9) Two disjoint edges + isolated node
        {5, {{0,1},{3,4}}},
        // 10) 5-cycle + small tree
        {10, {{0,1},{1,2},{2,3},{3,4},{4,0},{5,6},{6,7},{6,8},{8,9}}}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < (int)tests.size(); ++i) {
            long long r = sol.maxScore(tests[i].n, tests[i].edges);
            checksum ^= static_cast<int>(r ^ (r >> 32));
        }
        sink = checksum;
    }

    return 0;
}