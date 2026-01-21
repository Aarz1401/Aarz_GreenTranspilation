int main() {
    Solution sol;
    const std::vector<std::vector<int>> tests = {
        {1, 2, 3},
        {5, 2, 4},
        {1000000000, 2, 3},
        {999999937, 40000, 39999},
        {123456789, 7, 11},
        {987654321, 6, 9},
        {500000000, 40000, 40000},
        {42, 999, 1000},
        {10, 7, 13},
        {214748364, 32768, 16384}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.nthMagicalNumber(t[0], t[1], t[2]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}