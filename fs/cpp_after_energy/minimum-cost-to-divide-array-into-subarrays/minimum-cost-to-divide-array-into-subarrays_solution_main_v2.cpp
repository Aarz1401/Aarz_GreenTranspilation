int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1
    tests.push_back({{5}, {3}, 2});

    // Test 2
    tests.push_back({{1, 2}, {3, 4}, 5});

    // Test 3
    tests.push_back({{3, 1, 4, 1, 5}, {2, 7, 1, 8, 2}, 3});

    // Test 4: increasing nums and costs
    {
        vector<int> nums, cost;
        for (int i = 1; i <= 8; ++i) {
            nums.push_back(10 * i);
            cost.push_back(i);
        }
        tests.push_back({nums, cost, 4});
    }

    // Test 5: uniform nums, patterned cost
    {
        vector<int> nums(10, 1), cost;
        for (int i = 0; i < 10; ++i) {
            int v = (i % 3 == 0 ? 2 : (i % 3 == 1 ? 5 : 3));
            cost.push_back(v);
        }
        tests.push_back({nums, cost, 1});
    }

    // Test 6: descending nums, varied costs
    {
        vector<int> nums, cost;
        for (int i = 12; i >= 1; --i) {
            nums.push_back(i * 2);
        }
        for (int i = 12; i >= 1; --i) {
            cost.push_back((i * 5) % 9 + 1);
        }
        tests.push_back({nums, cost, 7});
    }

    // Test 7: larger nums
    {
        vector<int> nums, cost;
        for (int i = 1; i <= 15; ++i) {
            nums.push_back(i * 100 + (i % 7));
            cost.push_back(16 - i);
        }
        tests.push_back({nums, cost, 10});
    }

    // Test 8: quadratic pattern nums, modular cost
    {
        vector<int> nums, cost;
        for (int i = 1; i <= 18; ++i) {
            nums.push_back((i * i) % 50 + 1);
            cost.push_back((i * 7) % 10 + 1);
        }
        tests.push_back({nums, cost, 6});
    }

    // Test 9: Fibonacci-like nums, small cyclic costs
    {
        vector<int> nums, cost;
        int a = 1, b = 2;
        nums.push_back(a);
        nums.push_back(b);
        for (int i = 3; i <= 20; ++i) {
            int c = a + b;
            nums.push_back(c);
            a = b;
            b = c;
        }
        for (int i = 1; i <= 20; ++i) {
            cost.push_back((i % 5) + 1);
        }
        tests.push_back({nums, cost, 8});
    }

    // Test 10: alternating pattern
    {
        vector<int> nums, cost;
        for (int i = 1; i <= 25; ++i) {
            int v = (i % 4 == 0 ? 100 : (i % 4 == 1 ? 30 : (i % 4 == 2 ? 60 : 10)));
            nums.push_back(v);
            cost.push_back((i % 7) + 1);
        }
        tests.push_back({nums, cost, 9});
    }

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            long long res = sol.minimumCost(tests[i].nums, tests[i].cost, tests[i].k);
            checksum += static_cast<int>(res);
        }
        sink = checksum;
    }

    return 0;
}