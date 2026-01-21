int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1: Single element
    tests.push_back(TestCase{
        1,
        {5},
        0,
        {{0,0}, {0,0}}
    });

    // Test 2: Two equal elements with maxDiff = 0
    tests.push_back(TestCase{
        2,
        {1,1},
        0,
        {{0,1}, {1,0}, {0,0}, {1,1}}
    });

    // Test 3: Increasing sequence, large maxDiff
    tests.push_back(TestCase{
        5,
        {1,2,3,4,5},
        10,
        {{0,4}, {4,0}, {1,3}, {2,2}}
    });

    // Test 4: One large gap causing disconnection
    tests.push_back(TestCase{
        5,
        {0,2,100,101,102},
        3,
        {{0,1}, {1,2}, {3,4}, {0,4}, {2,4}}
    });

    // Test 5: Mixed negatives, duplicates, and large value
    tests.push_back(TestCase{
        10,
        {-5, -5, 0, 7, 7, 8, 20, -1, 3, 3},
        2,
        {{0,1}, {2,9}, {7,6}, {3,4}, {8,9}, {2,7}}
    });

    // Test 6: All equal elements, maxDiff = 0
    tests.push_back(TestCase{
        8,
        {5,5,5,5,5,5,5,5},
        0,
        {{0,7}, {3,4}, {1,6}, {2,2}}
    });

    // Test 7: Decreasing sequence, adjacent diffs within maxDiff
    {
        vector<int> nums7;
        for (int v = 30; v >= 16; --v) nums7.push_back(v);
        tests.push_back(TestCase{
            (int)nums7.size(),
            nums7,
            1,
            {{0,14}, {14,0}, {7,8}, {1,13}, {5,5}}
        });
    }

    // Test 8: Alternating low/high values -> two segments with maxDiff = 3
    tests.push_back(TestCase{
        12,
        {1,10,2,11,3,12,4,13,5,14,6,15},
        3,
        {{0,10}, {1,11}, {0,5}, {6,7}, {2,4}, {8,9}, {3,8}}
    });

    // Test 9: 50 elements with periodic large jumps (segments per 10 elements)
    {
        vector<int> nums9;
        for (int i = 0; i < 50; ++i) nums9.push_back(i + (i/10)*100);
        tests.push_back(TestCase{
            (int)nums9.size(),
            nums9,
            2,
            {{0,10}, {9,10}, {5,25}, {15,19}, {35,49}, {0,49}, {22,27}, {11,12}}
        });
    }

    // Test 10: 64 elements repeating pattern, maxDiff = 0 (only equal values connected)
    {
        vector<int> nums10;
        nums10.reserve(64);
        for (int i = 0; i < 64; ++i) nums10.push_back(i % 8);
        tests.push_back(TestCase{
            (int)nums10.size(),
            nums10,
            0,
            {{0,8}, {7,15}, {0,7}, {16,24}, {32,33}, {9,17}, {40,48}, {5,13}}
        });
    }

    Solution sol;

    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::microseconds;

    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        checksum += runOnce(sol, tests);
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}