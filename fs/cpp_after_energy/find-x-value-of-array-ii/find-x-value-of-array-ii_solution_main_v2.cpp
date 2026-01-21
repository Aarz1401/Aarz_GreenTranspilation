int main() {
    vector<TestCase> tests;

    // Test 1
    tests.push_back({
        {5},
        1,
        {{0, 7, 0, 1}}
    });

    // Test 2
    tests.push_back({
        {1, 2, 3},
        2,
        {
            {1, 5, 0, 0},
            {0, -3, 1, 1},
            {2, 4, 2, 2}
        }
    });

    // Test 3
    tests.push_back({
        {-5, 7, 0, 12, -3},
        3,
        {
            {3, -2, 0, 0},
            {1, 9, 2, 1},
            {4, 6, 1, 2},
            {0, -7, 4, 3}
        }
    });

    // Test 4
    tests.push_back({
        {2, 4, 6, 8},
        4,
        {
            {2, 5, 0, 0},
            {3, -1, 1, 1},
            {0, 7, 2, 2},
            {1, 3, 3, 4}
        }
    });

    // Test 5
    tests.push_back({
        {1, 1, 1, 1, 1, 1},
        5,
        {
            {5, 2, 0, 0},
            {4, 3, 1, 1},
            {3, 4, 2, 2},
            {2, 5, 3, 3},
            {1, 6, 4, 4},
            {0, 7, 5, 5}
        }
    });

    // Test 6
    tests.push_back({
        {-10, 3, -7, 9, 0, 2, 5},
        7,
        {
            {6, -2, 0, 0},
            {5, 14, 1, 3},
            {4, -21, 2, 5},
            {3, 7, 3, 7},
            {2, 8, 4, 2}
        }
    });

    // Test 7
    tests.push_back({
        {1000000, -1000000},
        8,
        {
            {1, 123456, 0, 0},
            {0, -654321, 1, 4},
            {1, 1, 1, 8}
        }
    });

    // Test 8
    tests.push_back({
        {1,2,3,4,5,6,7,8},
        10,
        {
            {7, 9, 0, 0},
            {6, -5, 2, 5},
            {5, 11, 4, 7},
            {4, -13, 6, 9},
            {3, 17, 7, 10},
            {2, 19, 5, 3}
        }
    });

    // Test 9
    tests.push_back({
        {0,1,2,3,4,5,6,7,8,9},
        9,
        {
            {9, -1, 0, 0},
            {8, -2, 1, 1},
            {7, -3, 2, 2},
            {6, -4, 3, 3},
            {5, -5, 4, 4},
            {4, -6, 5, 5},
            {3, -7, 6, 6},
            {2, -8, 7, 7},
            {1, -9, 8, 8},
            {0, -10, 9, 9}
        }
    });

    // Test 10
    tests.push_back({
        {9, -4, 6},
        6,
        {
            {2, 1000000007, 0, 0},
            {1, -1000000007, 1, 3},
            {0, 123456789, 2, 6}
        }
    });

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t t = 0; t < tests.size(); ++t) {
            Solution sol;
            vector<int> nums = tests[t].nums;
            int k = tests[t].k;
            vector<vector<int>> queries = tests[t].queries;
            vector<int> out = sol.resultArray(nums, k, queries);
            for (int v : out) checksum += v;
        }
        sink = checksum;
    }

    return 0;
}