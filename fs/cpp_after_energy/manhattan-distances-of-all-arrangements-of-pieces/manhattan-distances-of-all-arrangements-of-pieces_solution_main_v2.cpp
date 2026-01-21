int main() {
    vector<tuple<int,int,int>> tests = {
        {1, 1, 1},
        {1, 2, 2},
        {2, 2, 2},
        {2, 3, 3},
        {3, 3, 5},
        {5, 4, 6},
        {10, 10, 2},
        {20, 15, 10},
        {50, 40, 20},
        {100, 100, 50}
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            int m, n, k;
            tie(m, n, k) = t;
            long long res = s.distanceSum(m, n, k);
            checksum = (int)((checksum + res) % 1000000007);
        }
        sink = checksum;
    }
    return 0;
}