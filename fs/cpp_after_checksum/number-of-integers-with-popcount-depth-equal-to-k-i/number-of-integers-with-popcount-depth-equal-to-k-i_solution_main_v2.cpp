int main() {
    Solution sol;

    vector<pair<long long, int>> tests = {
        {1LL, 0},
        {1LL, 1},
        {3LL, 2},
        {5LL, 2},
        {100LL, 1},
        {1048576LL, 3},
        {562949953421311LL, 1},
        {999999999999999LL, 0},
        {1000000000000000LL, 1},
        {12345LL, 4}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += static_cast<int>(sol.popcountDepth(t.first, t.second));
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}