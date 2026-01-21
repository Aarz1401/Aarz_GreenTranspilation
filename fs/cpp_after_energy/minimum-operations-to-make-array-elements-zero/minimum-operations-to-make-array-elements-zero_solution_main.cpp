int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<vector<int>>> tests;
    tests.reserve(10);

    // 1) Minimal interval
    tests.push_back({{1, 1}});

    // 2) Small intervals spanning first group and boundary
    tests.push_back({{1, 3}, {4, 4}});

    // 3) Interval spanning across 1..3 and 4..7
    tests.push_back({{2, 7}});

    // 4) Singletons at powers of two within different 4^k buckets
    tests.push_back({{4, 4}, {8, 8}, {16, 16}});

    // 5) Large continuous interval
    tests.push_back({{1, 1000000}});

    // 6) Two large separated intervals
    tests.push_back({{1000000, 2000000}, {3000000, 4000000}});

    // 7) Large mid-range interval
    tests.push_back({{123456789, 223456789}});

    // 8) Interval near INT_MAX
    tests.push_back({{INT_MAX - 1000, INT_MAX}});

    // 9) Many small mixed intervals including l=0
    {
        vector<vector<int>> t9;
        t9.push_back({0, 50});
        for (int i = 1; i <= 50; ++i) {
            int l = i * 3;
            int r = l + (i % 5);
            t9.push_back({l, r});
        }
        tests.push_back(move(t9));
    }

    // 10) Programmatically generated diverse intervals
    {
        vector<vector<int>> t10;
        t10.reserve(300);
        int base = 25000000;
        for (int i = 1; i <= 300; ++i) {
            int l = base + (i * 12345 % 1000000);
            int len = 50 + (i * 37 % 5000);
            long long r64 = (long long)l + len;
            int r = (r64 > INT_MAX) ? INT_MAX : (int)r64;
            t10.push_back({l, r});
        }
        tests.push_back(move(t10));
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code here
        for (size_t i = 0; i < tests.size(); ++i) {
            long long res = sol.minOperations(tests[i]);
            // Mix with iter and index to prevent optimization
            checksum ^= (res + static_cast<long long>(i) + static_cast<long long>(iter));
            checksum = (checksum << 1) | (checksum >> 63); // rotate to mix bits
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}