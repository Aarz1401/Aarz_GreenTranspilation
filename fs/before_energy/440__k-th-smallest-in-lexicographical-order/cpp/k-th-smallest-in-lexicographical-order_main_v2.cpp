int main() {
    std::vector<std::pair<int,int>> tests = {
        {1, 1},
        {13, 2},
        {13, 6},
        {100, 90},
        {1000, 1},
        {1000, 1000},
        {1000000, 123456},
        {1000000000, 1},
        {1000000000, 1000000000},
        {123456789, 98765432}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.findKthNumber(t.first, t.second);
        }
        sink = checksum;
    }

    return 0;
}