int main() {
    vector<TestCase> tests = {
        {1, {}},
        {2, {1}},
        {3, {0}},
        {4, {2}},
        {5, {0, 4}},
        {10, {1, 2, 3, 4, 5, 6, 7, 8}},
        {7, {5, 6}},
        {1000, {}},
        {1000, {0, 10, 999, 500, 250, 750, 333, 666, 100, 900}},
        {100000, {0, 1, 2, 3, 4, 5, 42, 123, 4567, 54321, 75000, 99998, 99999}}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            Solution sol(t.N, t.blacklist);
            checksum += sol.pick();
        }
        sink = checksum;
    }
    return 0;
}