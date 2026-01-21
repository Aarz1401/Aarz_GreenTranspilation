int main() {
    // Prepare 10 diverse test cases
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Single element
    tests.push_back({{5}, {3}, 10});

    // 2) Two elements, small values, k = 0
    tests.push_back({{1, 2}, {2, 1}, 0});

    // 3) All equal nums and costs
    tests.push_back({vector<int>(10, 7), vector<int>(10, 7), 5});

    // 4) Increasing nums, uniform cost
    {
        int n = 100;
        vector<int> nums(n), cost(n, 1);
        for (int i = 0; i < n; ++i) nums[i] = i + 1;
        tests.push_back({move(nums), move(cost), 3});
    }

    // 5) Decreasing nums, increasing cost
    {
        int n = 100;
        vector<int> nums(n), cost(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = n - i;
            cost[i] = i + 1;
        }
        tests.push_back({move(nums), move(cost), 2});
    }

    // 6) Random moderate size
    {
        int n = 200;
        vector<int> nums(n), cost(n);
        mt19937 rng(123456);
        uniform_int_distribution<int> dnum(0, 1000);
        uniform_int_distribution<int> dcost(1, 100);
        for (int i = 0; i < n; ++i) {
            nums[i] = dnum(rng);
            cost[i] = dcost(rng);
        }
        tests.push_back({move(nums), move(cost), 7});
    }

    // 7) Large values
    {
        int n = 500;
        vector<int> nums(n, 1000000);
        vector<int> cost(n);
        for (int i = 0; i < n; ++i) cost[i] = 1000000 - (i % 1000);
        tests.push_back({move(nums), move(cost), 1000});
    }

    // 8) Alternating high/low pattern
    {
        int n = 256;
        vector<int> nums(n), cost(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = (i % 2 == 0) ? 0 : 1000000;
            cost[i] = (i % 2 == 0) ? 1 : 1000;
        }
        tests.push_back({move(nums), move(cost), 50});
    }

    // 9) Sparse zeros in cost
    {
        int n = 300;
        vector<int> nums(n), cost(n);
        mt19937 rng(789012);
        uniform_int_distribution<int> dnum(0, 1000);
        for (int i = 0; i < n; ++i) {
            nums[i] = dnum(rng);
            cost[i] = (i % 10 == 0) ? 100 : 0;
        }
        tests.push_back({move(nums), move(cost), 5});
    }

    // 10) Wave-like patterns
    {
        int n = 600;
        vector<int> nums(n), cost(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = (i * 1LL * i) % 1000;
            cost[i] = (i * 7) % 300 + 1;
        }
        tests.push_back({move(nums), move(cost), 17});
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            TestCase& t = tests[i];
            checksum += sol.minimumCost(t.nums, t.cost, t.k) ^ (long long)(iter + i);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}