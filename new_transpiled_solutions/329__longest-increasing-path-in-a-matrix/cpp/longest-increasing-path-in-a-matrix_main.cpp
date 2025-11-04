int main() {
    vector<vector<vector<int>>> test_cases;
    test_cases.reserve(10);

    // 1) Empty matrix
    test_cases.push_back(vector<vector<int>>{});

    // 2) Matrix with one empty row
    test_cases.push_back(vector<vector<int>>{vector<int>{}});

    // 3) Single element
    test_cases.push_back(vector<vector<int>>{{42}});

    // 4) Increasing row
    test_cases.push_back(vector<vector<int>>{{1, 2, 3, 4, 5}});

    // 5) Increasing column
    test_cases.push_back(vector<vector<int>>{{1}, {2}, {3}, {4}, {5}});

    // 6) LeetCode example with plateaus
    test_cases.push_back(vector<vector<int>>{{9, 9, 4}, {6, 6, 8}, {2, 1, 1}});

    // 7) Strictly decreasing grid (long increasing path from low to high)
    test_cases.push_back(vector<vector<int>>{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});

    // 8) Constant grid
    test_cases.push_back(vector<vector<int>>{{7, 7, 7}, {7, 7, 7}, {7, 7, 7}});

    // 9) Zigzag/serpentine
    test_cases.push_back(vector<vector<int>>{
        {10,  9,  4,  5},
        {11,  8,  7,  6},
        {12, 13, 14, 15},
        { 1,  2,  3, 16}
    });

    // 10) Mixed/random-like 5x5
    test_cases.push_back(vector<vector<int>>{
        { 7,  2,  3,  4,  5},
        {36, 35, 34, 33,  6},
        {37, 42, 43, 32,  7},
        {38, 41, 44, 31,  8},
        {39, 40, 45, 30,  9}
    });

    Solution sol;
    volatile long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& matrix : test_cases) {
            int r = sol.longestIncreasingPath(matrix);
            checksum += r;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}