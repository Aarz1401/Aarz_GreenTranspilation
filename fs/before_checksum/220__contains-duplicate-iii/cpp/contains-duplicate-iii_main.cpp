int main() {
    // Prepare 10 diverse test inputs
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Simple duplicate within k, t = 0
    tests.push_back(TestCase{{1, 2, 3, 1}, 3, 0});

    // 2) Negative numbers, t > 0 (floor division with negatives)
    tests.push_back(TestCase{{-3, -1, -4, -2}, 2, 1});

    // 3) Increasing sequence, no duplicates, small k, t = 0
    tests.push_back(TestCase{{1,2,3,4,5,6,7,8,9,10}, 1, 0});

    // 4) Near INT_MAX values, small t
    tests.push_back(TestCase{{INT_MAX, INT_MAX - 1, INT_MAX - 2, INT_MAX - 3}, 1, 1});

    // 5) k = 0 edge case, duplicates exist but should be false
    tests.push_back(TestCase{{1, 1}, 0, 0});

    // 6) Mixed signs with small k and t > 0
    tests.push_back(TestCase{{-10, 5, -6, 7, -8, 9}, 2, 3});

    // 7) Duplicate far apart but within large k
    {
        vector<int> v;
        v.reserve(60);
        for (int i = 0; i < 59; ++i) v.push_back(i);
        v.push_back(0); // duplicate of first element at the end
        tests.push_back(TestCase{move(v), 100, 0});
    }

    // 8) Repeating pattern, duplicates just beyond k (should be false)
    {
        vector<int> v(200);
        for (int i = 0; i < 200; ++i) v[i] = i % 50;
        tests.push_back(TestCase{move(v), 49, 0});
    }

    // 9) Larger increasing array, no duplicates, t = 0 (should be false)
    {
        vector<int> v(1000);
        for (int i = 0; i < 1000; ++i) v[i] = i;
        tests.push_back(TestCase{move(v), 100, 0});
    }

    // 10) Arithmetic progression including negatives, t large enough to match neighbors
    {
        vector<int> v;
        for (int x = -1000; x <= 1000; x += 10) v.push_back(x);
        tests.push_back(TestCase{move(v), 5, 10});
    }

    Solution sol;
    uint64_t checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run all test cases each iteration
        for (size_t i = 0; i < tests.size(); ++i) {
            // Work on a local reference; function does not modify nums
            auto& tc = tests[i];
            bool res = sol.containsNearbyAlmostDuplicate(tc.nums, tc.k, tc.t);
            // Mix iter and index into checksum to prevent optimization
            checksum += static_cast<uint64_t>(res) * (static_cast<uint64_t>(iter + 1) * 1315423911u + static_cast<uint64_t>(i));
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_us = duration_cast<microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}