int main() {
    vector<TestCase> tests;

    // Test 1
    tests.push_back(TestCase{
        {1, 2},
        {0}
    });

    // Test 2
    tests.push_back(TestCase{
        {2, 4, 6},
        {0, 1, 2}
    });

    // Test 3
    tests.push_back(TestCase{
        {2, 3, 5, 7},
        {0, 3, 5}
    });

    // Test 4
    tests.push_back(TestCase{
        {3, 6, 9, 12},
        {0, 2, 5}
    });

    // Test 5
    tests.push_back(TestCase{
        {1, 2, 3, 4, 5},
        {0, 4, 9}
    });

    // Test 6
    tests.push_back(TestCase{
        {10, 10, 5, 15, 20},
        {0, 5, 9}
    });

    // Test 7
    tests.push_back(TestCase{
        {12, 18, 24, 30, 36},
        {0, 6, 9}
    });

    // Test 8
    tests.push_back(TestCase{
        {8, 16, 32, 3, 6},
        {0, 1, 9}
    });

    // Test 9
    tests.push_back(TestCase{
        {14, 21, 28, 35, 42, 49},
        {0, 7, 14}
    });

    // Test 10
    tests.push_back(TestCase{
        {4, 6, 9, 10, 15, 25},
        {0, 5, 14}
    });

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tc : tests) {
            vector<int> out = sol.gcdValues(tc.nums, tc.queries);
            for (int v : out) checksum += v;
        }
        sink = checksum;
    }

    return 0;
}