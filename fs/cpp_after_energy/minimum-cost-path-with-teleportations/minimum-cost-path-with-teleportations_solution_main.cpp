int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<pair<vector<vector<int>>, int>> tests;

    // 1) 1x1 grid, k=0
    vector<vector<int>> grid1 = {{0}};
    tests.emplace_back(grid1, 0);

    // 2) 2x2 grid, k=0
    vector<vector<int>> grid2 = {{1, 2}, {3, 4}};
    tests.emplace_back(grid2, 0);

    // 3) 3x3 grid with repeating values, k=1
    vector<vector<int>> grid3 = {
        {5, 1, 5},
        {1, 5, 1},
        {5, 1, 5}
    };
    tests.emplace_back(grid3, 1);

    // 4) 5x5 patterned grid, k=2
    vector<vector<int>> grid4(5, vector<int>(5, 0));
    for (int r = 0; r < 5; ++r) {
        for (int c = 0; c < 5; ++c) {
            grid4[r][c] = (r * 7 + c * 3) % 10;
        }
    }
    tests.emplace_back(grid4, 2);

    // 5) 10x10 gradient grid, k=3
    vector<vector<int>> grid5(10, vector<int>(10, 0));
    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 10; ++c) {
            grid5[r][c] = (r + c) % 10;
        }
    }
    tests.emplace_back(grid5, 3);

    // 6) 8x12 rectangular grid, k=4
    vector<vector<int>> grid6(8, vector<int>(12, 0));
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 12; ++c) {
            grid6[r][c] = (r * 3 + c * 2) % 7;
        }
    }
    tests.emplace_back(grid6, 4);

    // 7) 12x8 grid with 0 and 100 values, k=5
    vector<vector<int>> grid7(12, vector<int>(8, 0));
    for (int r = 0; r < 12; ++r) {
        for (int c = 0; c < 8; ++c) {
            grid7[r][c] = ((r * r + c) % 2) ? 100 : 0;
        }
    }
    tests.emplace_back(grid7, 5);

    // 8) 15x15 all zeros, k=10
    vector<vector<int>> grid8(15, vector<int>(15, 0));
    tests.emplace_back(grid8, 10);

    // 9) 4x4 all same value, k=6
    vector<vector<int>> grid9(4, vector<int>(4, 2));
    tests.emplace_back(grid9, 6);

    // 10) 20x20 patterned small values, k=8
    vector<vector<int>> grid10(20, vector<int>(20, 0));
    for (int r = 0; r < 20; ++r) {
        for (int c = 0; c < 20; ++c) {
            grid10[r][c] = (r * 17 + c * 23 + 5) % 5;
        }
    }
    tests.emplace_back(grid10, 8);

    Solution solver;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            auto& grid = tests[i].first;  // non-const to match function signature
            int k = tests[i].second;
            checksum += solver.minCost(grid, k);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed << "\n";

    return 0;
}