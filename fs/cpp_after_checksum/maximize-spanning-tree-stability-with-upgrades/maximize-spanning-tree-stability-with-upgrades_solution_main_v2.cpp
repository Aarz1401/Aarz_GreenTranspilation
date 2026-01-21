int main() {
    vector<TestCase> tests = {
        // 1) Simple optional edge, k=0
        {2, {{0,1,5,0}}, 0},
        // 2) One mandatory, others optional, k=1
        {3, {{0,1,7,1},{1,2,6,0},{0,2,4,0}}, 1},
        // 3) Mandatory cycle -> -1
        {3, {{0,1,5,1},{1,2,4,1},{0,2,3,1}}, 0},
        // 4) Disconnected after all edges -> -1
        {4, {{0,1,10,1},{2,3,9,0}}, 0},
        // 5) k > n-1, result from final 2*s
        {3, {{0,1,3,0},{1,2,2,0}}, 5},
        // 6) Pure optional spanning tree, k=0, result is last s
        {4, {{0,1,10,0},{1,2,9,0},{2,3,8,0},{0,2,7,0}}, 0},
        // 7) Mandatory high s, final 2*s smaller with k=1
        {4, {{0,1,50,1},{1,2,40,0},{2,3,20,0}}, 1},
        // 8) Zero-weight edges
        {3, {{0,1,0,1},{1,2,0,0}}, 0},
        // 9) Equal weights, large k
        {5, {{0,1,1,0},{1,2,1,0},{2,3,1,0},{3,4,1,0}}, 10},
        // 10) Mixed with multiple components and k=2
        {6, {{0,1,9,1},{2,3,8,1},{1,2,7,0},{3,4,6,0},{4,5,5,0},{0,2,4,0},{5,0,3,0}}, 2}
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            vector<vector<int>> edgesCopy = tc.edges;
            int res = sol.maxStability(tc.n, edgesCopy, tc.k);
            checksum += res;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}