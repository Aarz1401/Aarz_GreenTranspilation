int main() {
    // Define 10 diverse test grids (square matrices)
    std::vector<std::vector<std::vector<int>>> tests;

    // 1) n=1 trivial
    tests.push_back({
        {5}
    });

    // 2) n=2 no obstacles
    tests.push_back({
        {1, 2},
        {3, 4}
    });

    // 3) n=3 sample with obstacles, path exists
    tests.push_back({
        {0, 1, -1},
        {1, 0, -1},
        {1, 1,  1}
    });

    // 4) n=3 impossible path => result 0
    tests.push_back({
        {1, -1, 1},
        {-1, -1, 1},
        {1,  1, 1}
    });

    // 5) n=4 mixed, path exists
    tests.push_back({
        {1, 0, 0, 1},
        {1, -1, -1, 1},
        {1, 1,  1, 1},
        {0, -1, 1, 10}
    });

    // 6) n=5 with central high value and corridors
    tests.push_back({
        {1, 2, 3, 4, 5},
        {1, -1, -1, -1, 1},
        {1, -1, 10, -1, 1},
        {1, -1, -1, -1, 1},
        {5, 4, 3, 2, 1}
    });

    // 7) n=6 checker-style obstacles, multiple paths
    tests.push_back({
        {0, 1, 0, 1, 0, 1},
        {1, -1, 1, -1, 1, 0},
        {0, 1, 0, 1, 0, 1},
        {1, -1, 1, -1, 1, 0},
        {0, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 1, 0}
    });

    // 8) n=7 pockets of cherries surrounded by obstacles, border paths
    tests.push_back({
        {1, 0, 0, 0, 0, 0, 1},
        {0, -1, -1, -1, -1, 0, 0},
        {0, -1, 5,  5,  -1, 0, 0},
        {0, -1, 5,  5,  -1, 0, 0},
        {0, -1, -1, -1, -1, 0, 0},
        {0, 0,  0,  0,  0,  0, 0},
        {1, 0,  0,  0,  0,  0, 1}
    });

    // 9) n=8 ring with rich inner pockets and obstacles
    tests.push_back({
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, -1, -1, -1, -1, -1, -1, 1},
        {1, -1, 2,  2,  2,  2,  -1, 1},
        {1, -1, 2,  -1, -1, 2,  -1, 1},
        {1, -1, 2,  -1, -1, 2,  -1, 1},
        {1, -1, 2,  2,  2,  2,  -1, 1},
        {1, -1, -1, -1, -1, -1, -1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    });

    // 10) n=10 larger mixed grid, guaranteed border paths
    tests.push_back({
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, -1, 1, -1, 1, -1, 1, -1, 1, 2},
        {2, 1, 2, 1, 2, 1, 2, 1, 2, 3},
        {3, -1, 3, -1, 3, -1, 3, -1, 3, 4},
        {4, 3, 4, 3, 4, 3, 4, 3, 4, 5},
        {5, -1, 5, -1, 5, -1, 5, -1, 5, 6},
        {6, 5, 6, 5, 6, 5, 6, 5, 6, 7},
        {7, -1, 7, -1, 7, -1, 7, -1, 7, 8},
        {8, 7, 8, 7, 8, 7, 8, 7, 8, 9},
        {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}
    });

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            std::vector<std::vector<int>> grid = t; // ensure non-const and avoid accidental mutation carryover
            checksum += sol.cherryPickup(grid);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}