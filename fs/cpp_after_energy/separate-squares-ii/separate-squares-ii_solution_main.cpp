int main() {
    // Prepare 10 diverse test inputs
    vector<vector<vector<int>>> tests;

    // 1. Single small square
    tests.push_back({{0, 0, 2}});

    // 2. Two non-overlapping squares
    tests.push_back({{0, 0, 3}, {5, 1, 2}});

    // 3. Two partially overlapping squares
    tests.push_back({{0, 0, 4}, {2, 1, 3}});

    // 4. Nested squares
    tests.push_back({{0, 0, 10}, {2, 2, 6}, {4, 4, 2}});

    // 5. Grid of small unit squares (5x5)
    {
        vector<vector<int>> t;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                t.push_back({i * 2, j * 2, 1});
            }
        }
        tests.push_back(std::move(t));
    }

    // 6. Very large coordinates
    tests.push_back({{-1000000000, -1000000000, 1500000000}});

    // 7. Many overlapping horizontal squares
    {
        vector<vector<int>> t;
        for (int i = 0; i < 50; ++i) {
            t.push_back({i, 0, 10});
        }
        tests.push_back(std::move(t));
    }

    // 8. Edge-touching squares
    tests.push_back({{0, 0, 10}, {10, 0, 10}, {20, 0, 10}, {30, 0, 10}, {0, 10, 10}, {10, 10, 10}});

    // 9. Negative coordinates with overlaps
    tests.push_back({{-5, -5, 3}, {-2, -1, 4}, {-10, 0, 5}});

    // 10. Pattern-generated diverse squares
    {
        vector<vector<int>> t;
        for (int i = 0; i < 100; ++i) {
            int x = (i % 11) * 3 - 15;
            int y = (i % 13) * 2 - 12;
            int len = (i % 9) + 1;
            t.push_back({x, y, len});
        }
        tests.push_back(std::move(t));
    }

    Solution sol;
    double checksum = 0.0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            auto& squares = tests[t];
            double res = sol.separateSquares(squares);
            checksum += res * (static_cast<int>(t) + 1);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    cout << fixed << setprecision(6);
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}