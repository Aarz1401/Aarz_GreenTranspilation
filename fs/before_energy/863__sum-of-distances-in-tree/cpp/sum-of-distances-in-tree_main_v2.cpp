int main() {
    vector<TestCase> tests = {
        {2, {{0,1}}},
        {3, {{0,1},{1,2}}},
        {4, {{0,1},{0,2},{0,3}}},
        {5, {{0,1},{1,2},{2,3},{3,4}}},
        {6, {{0,1},{0,2},{1,3},{1,4},{2,5}}},
        {7, {{3,0},{3,1},{3,2},{3,4},{3,5},{3,6}}},
        {8, {{0,1},{1,2},{1,3},{2,4},{2,5},{3,6},{6,7}}},
        {9, {{0,1},{0,2},{2,3},{2,4},{4,5},{5,6},{6,7},{6,8}}},
        {10, {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{5,8},{5,9}}},
        {12, {{0,1},{0,2},{0,3},{1,4},{1,5},{2,6},{2,7},{3,8},{8,9},{9,10},{10,11}}}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tc : tests) {
            vector<int> res = sol.sumOfDistancesInTree(tc.N, tc.edges);
            for (int v : res) {
                checksum += v;
            }
        }
        sink = checksum;
    }

    return 0;
}