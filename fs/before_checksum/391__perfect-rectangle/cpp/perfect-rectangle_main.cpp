int main() {
    // Define 10 diverse test inputs
    vector<vector<vector<int>>> tests;

    // 0: Two rectangles forming a perfect 2x2 rectangle vertically
    tests.push_back({
        {1, 1, 3, 2},
        {1, 2, 3, 3}
    });

    // 1: Complex valid tiling (LeetCode-style valid example)
    tests.push_back({
        {1,1,3,3},
        {3,1,4,2},
        {3,2,4,4},
        {1,3,2,4},
        {2,3,3,4},
        {1,1,2,2},
        {2,2,3,3},
        {1,2,2,3},
        {2,1,3,2}
    });

    // 2: Overlapping rectangles (invalid)
    tests.push_back({
        {1,1,2,3},
        {1,3,2,4},
        {3,1,4,2},
        {2,2,4,4}
    });

    // 3: Hole in the middle (invalid)
    tests.push_back({
        {1,1,3,3},
        {3,1,4,2},
        {3,2,4,4},
        {1,3,2,4},
        {2,3,3,4},
        {1,1,2,2},
        {1,2,2,3},
        {2,1,3,2}
    });

    // 4: Four rectangles forming a 2x2 square (valid)
    tests.push_back({
        {0,0,1,1},
        {1,0,2,1},
        {0,1,1,2},
        {1,1,2,2}
    });

    // 5: Single rectangle (valid)
    tests.push_back({
        {5,5,10,10}
    });

    // 6: Duplicate identical rectangles (invalid)
    tests.push_back({
        {0,0,1,1},
        {0,0,1,1}
    });

    // 7: Negative coordinates, two rectangles side-by-side (valid)
    tests.push_back({
        {-3,-1,-1,1},
        {-1,-1,1,1}
    });

    // 8: Disjoint rectangles (likely invalid)
    tests.push_back({
        {0,0,1,1},
        {2,0,3,1}
    });

    // 9: Large coordinates tiling a big rectangle with 10 vertical stripes (valid)
    {
        vector<vector<int>> big;
        int x0 = 100000000;
        int y0 = 200000000;
        for (int i = 0; i < 10; ++i) {
            big.push_back({x0 + i, y0, x0 + i + 1, y0 + 5});
        }
        tests.push_back(big);
    }

    Solution sol;
    uint64_t checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run all test cases
        for (size_t i = 0; i < tests.size(); ++i) {
            bool res = sol.isRectangleCover(tests[i]);
            // Mix into checksum to prevent optimization
            checksum = (checksum * 1315423911ull) ^ static_cast<uint64_t>(res + i + tests[i].size());
        }
    }

    auto end = clock::now();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << ns << "\n";
    return 0;
}