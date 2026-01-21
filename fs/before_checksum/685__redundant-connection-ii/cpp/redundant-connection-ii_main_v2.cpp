int main() {
    // 10 diverse valid test inputs
    vector<vector<vector<int>>> tests = {
        {{1,2},{1,3},{2,3}},                               // two-parent, no cycle
        {{1,2},{2,3},{3,4},{4,1},{1,5}},                   // cycle, no two-parent
        {{2,1},{3,1},{4,2},{1,4}},                         // both: cycle + two-parent
        {{1,2},{1,3},{2,4},{3,4},{4,5}},                   // two-parent, no cycle
        {{1,2},{1,3},{2,4},{3,5},{5,6},{6,1}},             // cycle, no two-parent
        {{1,2},{2,1}},                                     // small cycle
        {{1,2},{1,3},{2,4},{2,5},{3,5},{3,6},{6,7}},       // two-parent, no cycle
        {{4,2},{1,2},{2,3},{3,4},{2,5}},                   // both: cycle + two-parent
        {{1,2},{1,3},{2,4},{3,5},{4,6},{6,1}},             // cycle, no two-parent
        {{1,2},{2,3},{3,4},{1,3}}                          // two-parent, no cycle
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            vector<int> r = sol.findRedundantDirectedConnection(t);
            checksum += r[0] * 131 + r[1];
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}