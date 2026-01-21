int main() {
    vector<vector<string>> tests = {
        {"@.a"},
        {"@..a..b"},
        {"@.a.A.b"},
        {"@#..","...#","..a."},
        {"@..A","##.#","a..b"},
        {"@.a.#","###.#","b.A.B"},
        {"@..aA","..B#.","....b"},
        {"@abc"},
        {"@Aa"},
        {"@.a..","###.#","b.A.B","..c.."}
    };

    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& grid : tests) {
            checksum += sol.shortestPathAllKeys(grid);
        }
        sink = checksum;
    }
    return 0;
}