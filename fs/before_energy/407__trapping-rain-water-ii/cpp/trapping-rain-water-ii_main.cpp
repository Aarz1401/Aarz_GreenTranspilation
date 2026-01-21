int main() {
    // Define 10 diverse test inputs
    vector<vector<int>> t1; // empty

    vector<vector<int>> t2 = {
        {5}
    };

    vector<vector<int>> t3 = {
        {3, 1, 2, 4, 0, 1, 3} // single row
    };

    vector<vector<int>> t4 = {
        {3},
        {0},
        {2},
        {0},
        {4} // single column
    };

    vector<vector<int>> t5 = {
        {5, 5, 5},
        {5, 1, 5},
        {5, 5, 5} // bowl with center low
    };

    vector<vector<int>> t6 = {
        {3, 3, 3, 3},
        {3, 1, 2, 3},
        {3, 2, 1, 3},
        {3, 3, 3, 3} // interior valley
    };

    vector<vector<int>> t7 = {
        {5, 5, 5, 5, 5},
        {5, 1, 1, 1, 5},
        {0, 0, 0, 0, 0}, // boundary path to zero allows drainage
        {5, 1, 1, 1, 5},
        {5, 5, 5, 5, 5}
    };

    // Random 10x10 with fixed seed
    vector<vector<int>> t8(10, vector<int>(10));
    {
        mt19937 rng(123456789u);
        uniform_int_distribution<int> dist(0, 9);
        for (int i = 0; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                t8[i][j] = dist(rng);
    }

    // Gradient 30x30: higher at borders, lower inside
    vector<vector<int>> t9(30, vector<int>(30));
    {
        int m = 30, n = 30;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int d = min(min(i, m - 1 - i), min(j, n - 1 - j));
                int h = 9 - d;
                if (h < 0) h = 0;
                t9[i][j] = h;
            }
        }
    }

    // Flat 20x20 all same height
    vector<vector<int>> t10(20, vector<int>(20, 7));

    vector<vector<vector<int>>> tests;
    tests.reserve(10);
    tests.push_back(t1);
    tests.push_back(t2);
    tests.push_back(t3);
    tests.push_back(t4);
    tests.push_back(t5);
    tests.push_back(t6);
    tests.push_back(t7);
    tests.push_back(t8);
    tests.push_back(t9);
    tests.push_back(t10);

    Solution sol;
    long long checksum = 0;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.trapRainWater(tests[i]);
            checksum ^= (checksum << 1) ^ static_cast<long long>(i + 31);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}