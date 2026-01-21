int main() {
    vector<TestCase> tests = {
        {1, {1}, {2}, {}, 1},
        {2, {2,1}, {3,2}, {{1,2}}, 2},
        {3, {3,2,1}, {5,3,2}, {{1,2},{2,3}}, 3},
        {3, {1,2,3}, {1,4,7}, {{1,2},{1,3}}, 3},
        {4, {1,1,1,1}, {2,2,2,2}, {{1,2},{2,3},{3,4}}, 2},
        {4, {2,4,1,3}, {5,6,2,4}, {{1,2},{1,3},{1,4}}, 5},
        {5, {1,3,2,4,1}, {2,5,3,7,2}, {{1,2},{1,3},{3,4},{3,5}}, 4},
        {2, {5,5}, {10,10}, {{1,2}}, 0},
        {3, {2,2,2}, {3,3,3}, {{1,2},{1,3}}, 1},
        {5, {2,3,1,4,2}, {5,7,2,8,3}, {{1,2},{2,3},{3,4},{4,5}}, 6}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.maxProfit(t.n, const_cast<vector<int>&>(t.present), const_cast<vector<int>&>(t.future), const_cast<vector<vector<int>>&>(t.hierarchy), t.budget);
        }
        sink = checksum;
    }

    return 0;
}