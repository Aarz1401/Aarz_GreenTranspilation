int main() {
    // Define 10 diverse test inputs
    std::vector<std::vector<std::vector<int>>> datasets;

    // 1) Empty input
    datasets.push_back({});

    // 2) Single building
    datasets.push_back({
        {2, 9, 10}
    });

    // 3) Disjoint non-overlapping buildings
    datasets.push_back({
        {1, 2, 1},
        {3, 4, 2},
        {6, 7, 3}
    });

    // 4) Fully nested overlaps with increasing heights
    datasets.push_back({
        {1, 10, 3},
        {2, 9, 5},
        {3, 8, 7}
    });

    // 5) Touching endpoints with same heights
    datasets.push_back({
        {1, 3, 3},
        {3, 5, 3},
        {5, 7, 3}
    });

    // 6) Partial overlaps with same heights
    datasets.push_back({
        {1, 5, 3},
        {2, 6, 3},
        {4, 8, 3}
    });

    // 7) Overlapping chain with ascending heights
    datasets.push_back({
        {1, 3, 1},
        {2, 4, 2},
        {3, 5, 3},
        {4, 6, 4}
    });

    // 8) Overlapping chain with descending heights
    datasets.push_back({
        {1, 5, 4},
        {2, 6, 3},
        {3, 7, 2},
        {4, 8, 1}
    });

    // 9) Large coordinates and mixed overlaps
    datasets.push_back({
        {100000, 200000, 100},
        {150000, 250000, 120},
        {300000, 400000, 80},
        {400000, 500000, 200}
    });

    // 10) Complex mixed case
    datasets.push_back({
        {0, 2, 3},
        {1, 4, 4},
        {2, 3, 5},
        {6, 7, 2},
        {7, 8, 4},
        {8, 9, 1},
        {9, 12, 3},
        {10, 11, 6}
    });

    Solution sol;

    volatile uint64_t checksum = 0; // volatile to prevent optimization of the loop

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& ds : datasets) {
            auto buildings = ds; // make a local copy
            auto res = sol.getSkyline(buildings);
            for (const auto& p : res) {
                // Mix coordinates and heights into checksum
                checksum = checksum * 1315423911ull + static_cast<uint64_t>(p[0]) * 733ull + static_cast<uint64_t>(p[1]);
            }
            // Also mix in result size to avoid identical outputs canceling
            checksum ^= static_cast<uint64_t>(res.size() + 0x9e3779b97f4a7c15ULL);
        }
    }

    auto end = clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}