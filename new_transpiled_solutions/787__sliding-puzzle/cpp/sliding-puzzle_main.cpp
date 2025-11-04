int main() {
    // Define 10 diverse 2x3 sliding puzzle boards
    vector<vector<vector<int>>> tests = {
        {{1,2,3},{4,5,0}}, // solved
        {{1,2,3},{4,0,5}}, // 1 move
        {{1,2,0},{4,5,3}}, // solvable
        {{1,2,3},{5,4,0}}, // unsolvable
        {{4,1,2},{5,0,3}}, // LC example
        {{3,2,4},{1,5,0}}, // LC example
        {{1,0,2},{3,4,5}}, // solvable
        {{0,5,4},{3,2,1}}, // solvable, far
        {{2,1,3},{4,5,0}}, // unsolvable
        {{2,3,0},{1,4,5}}  // solvable
    };

    Solution solver;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            auto board = tests[i]; // copy since function takes non-const reference
            int res = solver.slidingPuzzle(board);
            checksum += res * static_cast<long long>(i + 1);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}