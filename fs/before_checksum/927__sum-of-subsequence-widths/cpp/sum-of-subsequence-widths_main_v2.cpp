int main() {
    std::vector<std::vector<int>> tests = {
        {1},
        {1, 2},
        {5, 5},
        {2, 2, 2, 2, 2},
        {4, 1, 3, 2},
        {1000000000, 1, 1000000000},
        {1000000000, 999999999, 123456789, 987654321},
        {7, 7, 3, 1, 9, 9, 5},
        {10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
        {42, 42, 42, 1, 2, 3, 100, 1000000000, 999999999, 12345, 67890}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            std::vector<int> v = t;
            int res = sol.sumSubseqWidths(v);
            checksum = (checksum + res) % 1000000007;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}