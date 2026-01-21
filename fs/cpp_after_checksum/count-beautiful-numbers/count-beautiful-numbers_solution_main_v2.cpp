int main() {
    Solution sol;
    vector<pair<long long, long long>> tests = {
        {0, 0},
        {1, 9},
        {10, 99},
        {100, 999},
        {0, 12345},
        {54321, 99999},
        {100000, 200000},
        {0, 999999},
        {123456, 123456},
        {700000, 765432}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += static_cast<int>(sol.beautifulNumbers(t.first, t.second));
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}