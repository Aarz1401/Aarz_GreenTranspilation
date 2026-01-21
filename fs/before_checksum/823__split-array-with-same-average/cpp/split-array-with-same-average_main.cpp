int main() {
    // 10 diverse test inputs
    vector<vector<int>> tests = {
        {1,2,3,4,5,6,7,8},                         // typical, expected true
        {3,1},                                      // small, expected false
        {1,2,3,4,5,6,7,8,9,10},                     // larger, expected true (e.g., {1,10})
        {0,0,0,0,0,0,0,0},                          // all zeros, true
        {1,1,1,1,1,1,1,1,1,1},                      // all equal, true
        {2,4,6,8,10,12},                            // evens, true (e.g., {2,12})
        {1,2,3,5},                                  // early impossible, false
        {18,0,16,2},                                // true (e.g., {16,2})
        {1},                                        // single element, false
        {9,1,2,3,10,12,7,8,4,6,5,11}                // mixed 1..12 shuffled, true (e.g., {5,8})
    };

    Solution sol;
    uint64_t checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            bool res = sol.splitArraySameAverage(tests[t]);
            // Accumulate checksum to prevent optimization
            checksum += res ? static_cast<uint64_t>((t + 1) * (iter + 1)) : 0ull;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}