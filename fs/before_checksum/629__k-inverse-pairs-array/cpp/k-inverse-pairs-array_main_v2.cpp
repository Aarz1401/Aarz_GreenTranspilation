int main() {
    Solution sol;

    vector<pair<int,int>> tests = {
        {1, 0},
        {2, 1},
        {3, 2},
        {4, 6},
        {5, 5},
        {10, 12},
        {15, 20},
        {20, 10},
        {30, 100},
        {50, 200}
    };

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.kInversePairs(t.first, t.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}