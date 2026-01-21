int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Prepare 10 diverse test cases
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Mixed small array
    tests.push_back(TestCase{
        {1, 2, 3, 2, 2, 3, 1, 4, 4, 4, 5, 5, 6, 1, 2, 3, 7, 7, 7, 8}, 5, 3
    });

    // 2) All same values
    {
        vector<int> v(200, 42);
        tests.push_back(TestCase{v, 50, 1});
    }

    // 3) Strictly increasing sequence
    {
        vector<int> v(500);
        for (int i = 0; i < 500; ++i) v[i] = i + 1;
        tests.push_back(TestCase{v, 100, 10});
    }

    // 4) Negative and positive mix with modular pattern
    {
        vector<int> v(256);
        for (int i = 0; i < 256; ++i) v[i] = (i * 7 % 101) - 50;
        tests.push_back(TestCase{v, 60, 8});
    }

    // 5) k = 1, small ranges
    {
        vector<int> v(100);
        for (int i = 0; i < 100; ++i) v[i] = (i * 31 + 7) % 9 - 4;
        tests.push_back(TestCase{v, 1, 1});
    }

    // 6) k = n, repeated pattern
    {
        vector<int> v(150);
        for (int i = 0; i < 150; ++i) v[i] = i % 20;
        tests.push_back(TestCase{v, 150, 20});
    }

    // 7) x = 0
    {
        vector<int> v(80);
        for (int i = 0; i < 80; ++i) v[i] = (i % 5) - 2;
        tests.push_back(TestCase{v, 10, 0});
    }

    // 8) Many distinct values in a higher range
    {
        vector<int> v(300);
        for (int i = 0; i < 300; ++i) v[i] = 1000 + i;
        tests.push_back(TestCase{v, 30, 15});
    }

    // 9) k > n (should result in empty output)
    {
        vector<int> v(30);
        for (int i = 0; i < 30; ++i) v[i] = (i * 97 + 12345) % 1000 - 500;
        tests.push_back(TestCase{v, 100, 10});
    }

    // 10) Large magnitude values alternating sign
    {
        vector<int> v(200);
        for (int i = 0; i < 200; ++i) {
            if (i % 2 == 0) v[i] = INT_MAX / 4 - i;
            else v[i] = INT_MIN / 4 + i;
        }
        tests.push_back(TestCase{v, 50, 25});
    }

    Solution sol;
    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            // Work on a non-const reference as required by the function signature
            auto& tc = tests[i];
            vector<long long> res = sol.findXSum(tc.nums, tc.k, tc.x);

            // Accumulate a checksum to prevent optimization
            for (size_t j = 0; j < res.size(); ++j) {
                checksum += res[j] + 1315423911ULL + ((iter + 1) * (i + 1) * (j + 1));
            }
            checksum += static_cast<long long>(res.size() * (i + 1) + iter);
        }
    }

    auto end = clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed(ns): " << elapsed_ns << "\n";

    return 0;
}