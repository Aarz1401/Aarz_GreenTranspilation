int main() {
    vector<TestCase> tests = {
        {1, 0, {0}},
        {1, 1, {1}},
        {2, 1, {1, 2}},
        {3, 2, {3, 5, -7}},
        {4, 0, {10, 0, 10}},
        {5, 3, {2, 2, 2, 2}},
        {6, 6, {1, 1, 1}},
        {6, 1, {123456789, -987654321}},
        {5, 5, {0, 0, 0, 0, 0}},
        {3, 0, {1000000006}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            int r = sol.magicalSum(tc.m, tc.k, const_cast<vector<int>&>(tc.nums));
            checksum += r;
            if (checksum >= 1000000007) checksum -= 1000000007;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}