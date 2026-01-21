int main() {
    vector<TestCase> tests;

    tests.push_back(TestCase{
        {1},
        {{0, 0, 1}, {0, 0, 2}}
    });

    tests.push_back(TestCase{
        {7, 7, 7, 7, 7},
        {{0, 4, 3}, {1, 3, 2}, {2, 2, 1}, {0, 4, 6}}
    });

    tests.push_back(TestCase{
        {1, 2, 3, 4, 5},
        {{0, 4, 3}, {1, 3, 2}, {1, 1, 1}}
    });

    tests.push_back(TestCase{
        {-5, -1, -5, -1, -5, 2},
        {{0, 5, 3}, {1, 3, 2}, {0, 2, 2}}
    });

    tests.push_back(TestCase{
        {1, 2, 1, 2, 1, 2},
        {{0, 5, 3}, {0, 3, 2}, {1, 4, 2}, {2, 3, 2}, {2, 3, 1}}
    });

    tests.push_back(TestCase{
        {1000000000, -1000000000, 1000000000, 5, 5, 5, 7},
        {{0, 6, 3}, {0, 2, 2}, {3, 6, 2}, {1, 1, 1}}
    });

    tests.push_back(TestCase{
        {3, 3, 3, 2, 2, 1, 1, 1, 1, 1},
        {{0, 9, 4}, {0, 2, 3}, {3, 4, 2}, {5, 9, 3}, {0, 9, 6}}
    });

    tests.push_back(TestCase{
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
        {{0, 9, 1}, {2, 5, 1}, {4, 4, 1}, {0, 9, 2}}
    });

    tests.push_back(TestCase{
        {1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4},
        {{0, 11, 4}, {0, 11, 5}, {2, 8, 3}, {8, 11, 3}}
    });

    tests.push_back(TestCase{
        {5, 1, 5, 2, 5, 3, 5, 4, 5, 5, 6, 5, 7, 5, 8, 5, 9, 5, 10, 5},
        {{0, 19, 7}, {1, 18, 6}, {10, 19, 4}, {1, 3, 2}, {0, 0, 1}}
    });

    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tc : tests) {
            vector<int> ans = sol.subarrayMajority(tc.nums, tc.queries);
            for (int v : ans) {
                checksum += v;
            }
        }
        sink = checksum;
    }
    return 0;
}