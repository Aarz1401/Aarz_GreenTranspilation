int main() {
    // Define 10 diverse test inputs
    vector<vector<vector<int>>> tests;
    // 1) 1x1 all ones
    tests.push_back({{1}});
    // 2) Small manual mixed grid
    tests.push_back({{1, 0, 2}, {2, 1, 0}});
    // 3) 3x5 checkerboard with some 1s
    {
        auto g = makeCheckerboard(3, 5, 3);
        g[0][2] = 1; g[2][2] = 1;
        tests.push_back(g);
    }
    // 4) 5x5 random
    tests.push_back(makeRandomGrid(5, 5, 42u, 0.2));
    // 5) 10x10 random
    tests.push_back(makeRandomGrid(10, 10, 123u, 0.1));
    // 6) 7x9 checkerboard with diagonal ones
    {
        auto g = makeCheckerboard(7, 9);
        for (int i = 0; i < 7 && i < 9; ++i) g[i][i] = 1;
        tests.push_back(g);
    }
    // 7) 20x20 stripes with periodic ones
    {
        vector<vector<int>> g(20, vector<int>(20, 0));
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                if ((i + j) % 7 == 0) g[i][j] = 1;
                else g[i][j] = ((i + j) % 2 == 0) ? 0 : 2;
            }
        }
        tests.push_back(g);
    }
    // 8) 15x15 with center cross of ones
    {
        vector<vector<int>> g(15, vector<int>(15, 0));
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                g[i][j] = ((i + j) % 2 == 0) ? 0 : 2;
            }
        }
        int c = 7;
        for (int i = 0; i < 15; ++i) { g[i][c] = 1; g[c][i] = 1; }
        tests.push_back(g);
    }
    // 9) 1x10 row alternating with ones at both ends
    {
        vector<vector<int>> g(1, vector<int>(10, 0));
        for (int j = 0; j < 10; ++j) g[0][j] = (j % 2 == 0) ? 0 : 2;
        g[0][0] = 1; g[0][9] = 1;
        tests.push_back(g);
    }
    // 10) 30x30 random dense
    tests.push_back(makeRandomGrid(30, 30, 987u, 0.12));

    Solution sol;
    long long checksum = 0;

    auto t0 = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            // Use by reference to avoid copy; function takes non-const reference
            checksum += sol.lenOfVDiagonal(tests[t]);
            checksum ^= (static_cast<long long>(t) << (iter % 7)); // perturb checksum
        }
    }
    auto t1 = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed << "\n";

    return 0;
}