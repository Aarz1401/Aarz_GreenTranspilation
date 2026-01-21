int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Prepare 10 diverse test inputs
    vector<vector<vector<int>>> tests;
    tests.reserve(10);

    // 1) Small overlapping intervals
    tests.push_back({
        {1,3}, {1,4}, {2,5}, {3,5}, {2,3}
    });

    // 2) Overlapping chain of intervals
    {
        vector<vector<int>> t;
        for (int i = 0; i < 20; ++i) {
            t.push_back({i, i + 2}); // length 3 (two integers min)
        }
        tests.push_back(move(t));
    }

    // 3) Disjoint intervals (each needs its own two points)
    {
        vector<vector<int>> t;
        for (int i = 0; i < 15; ++i) {
            int start = i * 3;
            t.push_back({start, start + 1}); // exactly two integers
        }
        tests.push_back(move(t));
    }

    // 4) Nested intervals (descending ends)
    {
        vector<vector<int>> t;
        for (int e = 20; e >= 10; --e) {
            t.push_back({1, e});
        }
        tests.push_back(move(t));
    }

    // 5) Many identical intervals
    {
        vector<vector<int>> t;
        for (int i = 0; i < 30; ++i) {
            t.push_back({5, 15});
        }
        tests.push_back(move(t));
    }

    // 6) Patterned intervals using modular arithmetic
    {
        vector<vector<int>> t;
        for (int i = 0; i < 50; ++i) {
            int start = (i * 7) % 60;
            int len = (i % 5) + 2;
            t.push_back({start, start + len});
        }
        tests.push_back(move(t));
    }

    // 7) High value intervals (to test large numbers)
    {
        vector<vector<int>> t;
        const int64_t base = 1000000000;
        for (int i = 0; i < 30; ++i) {
            int64_t s = base + static_cast<int64_t>(i) * 3;
            int64_t e = s + 5;
            t.push_back({static_cast<int>(s), static_cast<int>(e)});
        }
        tests.push_back(move(t));
    }

    // 8) Intervals with negative starts
    {
        vector<vector<int>> t;
        for (int i = 0; i < 20; ++i) {
            int start = -50 + i * 3;
            t.push_back({start, start + 10});
        }
        tests.push_back(move(t));
    }

    // 9) Single interval
    tests.push_back({
        {10, 20}
    });

    // 10) Mixed assorted intervals
    tests.push_back({
        {0,100}, {20,30}, {25,35}, {40,90}, {85,95},
        {50,51}, {60,70}, {65,66}, {67,80}, {10,12}, {11,13}, {12,14}
    });

    Solution sol;
    long long checksum = 0;

    auto start_time = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            auto intervals = tests[i]; // copy since the function mutates the input
            checksum += sol.intersectionSizeTwo(intervals);
        }
    }
    auto end_time = chrono::high_resolution_clock::now();

    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}