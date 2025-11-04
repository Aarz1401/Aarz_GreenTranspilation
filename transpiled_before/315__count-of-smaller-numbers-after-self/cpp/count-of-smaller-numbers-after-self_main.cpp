int main() {
    // Prepare 10 diverse test inputs
    vector<vector<int>> tests;
    tests.reserve(10);

    // 1. Empty
    tests.push_back({});

    // 2. Single element
    tests.push_back({42});

    // 3. Strictly ascending
    {
        vector<int> asc;
        for (int i = 1; i <= 16; ++i) asc.push_back(i);
        tests.push_back(move(asc));
    }

    // 4. Strictly descending
    {
        vector<int> desc;
        for (int i = 20; i >= 1; --i) desc.push_back(i);
        tests.push_back(move(desc));
    }

    // 5. All equal elements
    tests.push_back(vector<int>(12, 7));

    // 6. Mixed negatives and duplicates
    tests.push_back({5, 2, 6, 1, -1, 2, 2, 3, 0, -2, 5, 1});

    // 7. Random (fixed seed), size 128
    {
        mt19937 rng(123456);
        uniform_int_distribution<int> dist(-1000000, 1000000);
        vector<int> v(128);
        for (auto& x : v) x = dist(rng);
        tests.push_back(move(v));
    }

    // 8. Extremes including INT_MIN and INT_MAX
    tests.push_back({INT_MAX, INT_MIN, 0, -1, 1, INT_MAX, INT_MIN, 0, -2, 2});

    // 9. Alternating high/low pattern
    {
        vector<int> alt;
        for (int i = 0; i < 20; ++i) {
            if (i % 2 == 0) alt.push_back(1000 - i);
            else alt.push_back(-1000 + i);
        }
        tests.push_back(move(alt));
    }

    // 10. Another random (fixed seed), size 512
    {
        mt19937 rng(789);
        uniform_int_distribution<int> dist(-500000, 500000);
        vector<int> v(512);
        for (auto& x : v) x = dist(rng);
        tests.push_back(move(v));
    }

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code here
        for (size_t t = 0; t < tests.size(); ++t) {
            vector<int>& nums = tests[t];
            vector<int> res = sol.countSmaller(nums);
            for (size_t i = 0; i < res.size(); ++i) {
                // Mix in both result and input value to avoid optimization
                checksum += static_cast<long long>(res[i]) * (static_cast<long long>(i + 1) + (nums[i] & 0xFFFF));
            }
            checksum ^= static_cast<long long>(res.size()) << (t % 17);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed = end - start;

    cout << "Checksum: " << checksum << '\n';
    cout << "Elapsed time (ms): " << elapsed.count() << '\n';

    return 0;
}