int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) All zeros
    {
        TestCase tc;
        tc.s = string(10, '0');
        tc.queries = {
            {0, 9}, {0, 0}, {9, 9}, {2, 7}, {1, 2}
        };
        tests.push_back(std::move(tc));
    }

    // 2) All ones
    {
        TestCase tc;
        tc.s = string(10, '1');
        tc.queries = {
            {0, 9}, {1, 1}, {4, 7}, {0, 0}, {9, 9}
        };
        tests.push_back(std::move(tc));
    }

    // 3) Alternating pattern
    {
        TestCase tc;
        int n = 31;
        tc.s.reserve(n);
        for (int i = 0; i < n; ++i) tc.s.push_back((i % 2 == 0) ? '0' : '1');
        tc.queries = {
            {0, 30}, {1, 29}, {2, 2}, {15, 15}, {8, 23}, {10, 20}
        };
        tests.push_back(std::move(tc));
    }

    // 4) Clustered runs of zeros and ones
    {
        TestCase tc;
        tc.s = "000111000111000111";
        tc.queries = {
            {0, 5}, {3, 8}, {6, 11}, {12, 17}, {9, 15}, {0, 17}
        };
        tests.push_back(std::move(tc));
    }

    // 5) Zeros at ends, ones in middle
    {
        TestCase tc;
        tc.s = "00011111000";
        tc.queries = {
            {0, 10}, {0, 2}, {8, 10}, {3, 7}, {2, 8}
        };
        tests.push_back(std::move(tc));
    }

    // 6) Single zero
    {
        TestCase tc;
        tc.s = "0";
        tc.queries = {
            {0, 0}
        };
        tests.push_back(std::move(tc));
    }

    // 7) Single one
    {
        TestCase tc;
        tc.s = "1";
        tc.queries = {
            {0, 0}
        };
        tests.push_back(std::move(tc));
    }

    // 8) Mixed small with zero blocks at ends
    {
        TestCase tc;
        tc.s = "0011100";
        tc.queries = {
            {0, 6}, {0, 1}, {5, 6}, {2, 4}, {1, 5}
        };
        tests.push_back(std::move(tc));
    }

    // 9) Irregular pattern with varying run lengths
    {
        TestCase tc;
        tc.s = "101010001110000101011110000";
        tc.queries = {
            {0, 26}, {3, 5}, {7, 14}, {10, 16}, {20, 26}, {12, 12}
        };
        tests.push_back(std::move(tc));
    }

    // 10) Large patterned case
    {
        TestCase tc;
        string pattern = "00001111";
        int repeats = 625; // 8 * 625 = 5000
        tc.s.reserve(repeats * (int)pattern.size());
        for (int i = 0; i < repeats; ++i) tc.s += pattern;

        vector<vector<int>> q;
        q.push_back({0, (int)tc.s.size() - 1});
        for (int seg = 0; seg < 10; ++seg) {
            int l = seg * 500;
            int r = min((int)tc.s.size() - 1, l + 300);
            q.push_back({l, r});
        }
        for (int seg = 0; seg < 10; ++seg) {
            int l = seg * 250;
            int r = min((int)tc.s.size() - 1, l + 200);
            q.push_back({l, r});
        }
        q.push_back({123, 4567});
        q.push_back({1000, 2000});
        q.push_back({2500, 3500});
        q.push_back({4000, 4500});
        q.push_back({0, 0});
        q.push_back({(int)tc.s.size() - 1, (int)tc.s.size() - 1});
        tc.queries = std::move(q);
        tests.push_back(std::move(tc));
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t ti = 0; ti < tests.size(); ++ti) {
            auto res = sol.maxActiveSectionsAfterTrade(tests[ti].s, tests[ti].queries);
            for (size_t i = 0; i < res.size(); ++i) {
                checksum += res[i] + (long long)iter + (long long)ti + (long long)i;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}