int main() {
    // Define 10 diverse test cases
    std::vector<TestCase> tests = {
        { {1, 3, 1}, 1 },                               // duplicates, expect 0
        { {1, 6}, 1 },                                  // minimal size
        { {5, 5, 5, 5}, 6 },                            // all equal
        { {1, 2, 3, 4, 5}, 7 },                         // increasing sequence
        { {-10, -5, 0, 5, 10}, 8 },                     // negatives and positives
        { {1, 6, 1, 1, 6}, 7 },                         // many duplicates
        { {1, 1000000, 500000, 750000, 250000}, 4 },    // wide spread
        { {9, 4, 1, 7, 3, 8, 2, 6, 5}, 20 },            // shuffled 1..9
        { {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20}, 100 }, // 1..20
        { {100,1,50,2,50,3,50,4,50,5,100,1,50,2,50,3,50,4,50,5}, 150 } // repeats
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            std::vector<int> v = t.nums; // copy because the algorithm sorts in place
            checksum += sol.smallestDistancePair(v, t.k);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}