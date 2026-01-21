int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1
    {
        TestCase t;
        t.nums = {1};
        t.queries = {{0, 0, 1, 2}};
        tests.push_back(t);
    }

    // Test 2
    {
        TestCase t;
        t.nums = {5, 4, 3, 2, 1};
        t.queries = {
            {0, 4, 1, 3},
            {1, 4, 2, 5},
            {1, 4, 5, 7}
        };
        tests.push_back(t);
    }

    // Test 3
    {
        TestCase t;
        t.nums.resize(10);
        for (int i = 0; i < 10; ++i) t.nums[i] = i;
        t.queries = {
            {1, 7, 2, 11},
            {0, 9, 3, 13},
            {2, 8, 5, 7}
        };
        tests.push_back(t);
    }

    // Test 4
    {
        TestCase t;
        t.nums.resize(50);
        for (int i = 0; i < 50; ++i) t.nums[i] = i + 1;
        t.queries = {
            {0, 49, 7, 19},
            {5, 45, 9, 17},
            {10, 20, 2, 23}
        };
        tests.push_back(t);
    }

    // Test 5
    {
        TestCase t;
        t.nums.resize(100);
        for (int i = 0; i < 100; ++i) t.nums[i] = i + 1;
        t.queries = {
            {0, 99, 11, 29},
            {3, 97, 12, 31},
            {50, 99, 25, 37},
            {1, 50, 5, 41}
        };
        tests.push_back(t);
    }

    // Test 6
    {
        TestCase t;
        t.nums.assign(37, 2);
        t.queries = {
            {0, 36, 7, 43},
            {1, 35, 8, 47},
            {3, 20, 4, 53}
        };
        tests.push_back(t);
    }

    // Test 7
    {
        TestCase t;
        t.nums.resize(64);
        for (int i = 0; i < 64; ++i) t.nums[i] = (i * i) % 1000;
        t.queries = {
            {0, 63, 1, 3},
            {5, 60, 16, 97},
            {2, 30, 3, 7},
            {0, 63, 10, 59}
        };
        tests.push_back(t);
    }

    // Test 8
    {
        TestCase t;
        t.nums = {1000000006, 1000000006};
        t.queries = {
            {0, 1, 2, 5},
            {1, 1, 1, 3}
        };
        tests.push_back(t);
    }

    // Test 9
    {
        TestCase t;
        t.nums.resize(30);
        for (int i = 0; i < 30; ++i) t.nums[i] = (i % 7) + 1;
        t.queries = {
            {0, 29, 6, 13},
            {2, 28, 7, 17},
            {1, 19, 5, 19},
            {10, 10, 3, 23}
        };
        tests.push_back(t);
    }

    // Test 10
    {
        TestCase t;
        t.nums.resize(200);
        for (int i = 0; i < 200; ++i) t.nums[i] = ((i * 31 + 7) % 1000) + 1;
        t.queries = {
            {0, 199, 15, 7},
            {5, 195, 16, 11},
            {20, 180, 20, 17},
            {33, 150, 3, 19},
            {7, 123, 14, 23}
        };
        tests.push_back(t);
    }

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& test : tests) {
            vector<int> nums = test.nums;
            vector<vector<int>> queries = test.queries;
            Solution sol;
            checksum += sol.xorAfterQueries(nums, queries);
        }
        sink = checksum;
    }

    return 0;
}