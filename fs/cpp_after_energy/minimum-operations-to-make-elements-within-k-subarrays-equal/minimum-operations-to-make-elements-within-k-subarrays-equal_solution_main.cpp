int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Test> tests;

    // 1) Increasing sequence, x=1 (costs 0), k=5
    tests.push_back(Test{{1,2,3,4,5,6,7,8,9,10}, 1, 5});

    // 2) Random small array, x=2, k=2
    tests.push_back(Test{{5,1,9,3,14,2,8,6}, 2, 2});

    // 3) All equal numbers (costs 0), x=3, k=3
    tests.push_back(Test{{7,7,7,7,7,7,7,7,7}, 3, 3});

    // 4) Mixed negatives and positives, x=3, k=2
    tests.push_back(Test{{-10,-5,0,5,10,-3,3,-2,2,-1,1,4}, 3, 2});

    // 5) x > n (impossible), expect INF-like result
    tests.push_back(Test{{1,2,3,4,5}, 6, 1});

    // 6) k = 0 (no operations), expect 0
    tests.push_back(Test{{9,8,7,6,5,4,3}, 3, 0});

    // 7) Larger array (generated), x=5, k=10
    {
        vector<int> v;
        v.reserve(600);
        for (int i = 0; i < 600; ++i) {
            int val = static_cast<int>((i * 37LL) % 1000) - 500;
            v.push_back(val);
        }
        tests.push_back(Test{move(v), 5, 10});
    }

    // 8) Another larger array with different pattern, x=8, k=16
    {
        vector<int> v;
        v.reserve(400);
        for (int i = 0; i < 400; ++i) {
            int val = static_cast<int>((1LL * i * i + 3LL * i + 7) % 100) - 50;
            v.push_back(val);
        }
        tests.push_back(Test{move(v), 8, 16});
    }

    // 9) Single element, x=1, k=1 (cost 0)
    tests.push_back(Test{{42}, 1, 1});

    // 10) Exact fill: n=12, x=3, k=4
    tests.push_back(Test{{4,1,7,3,2,9,5,8,6,10,11,0}, 3, 4});

    Solution sol;

    auto start_time = high_resolution_clock::now();
    unsigned long long checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            long long res = sol.minOperations(t.nums, t.x, t.k);
            // Mix result into checksum to prevent optimization
            checksum ^= static_cast<unsigned long long>(res) + 0x9e3779b97f4a7c15ULL + static_cast<unsigned long long>(iter) + static_cast<unsigned long long>(t.nums.size());
        }
    }

    auto end_time = high_resolution_clock::now();
    long long elapsed_us = duration_cast<microseconds>(end_time - start_time).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}