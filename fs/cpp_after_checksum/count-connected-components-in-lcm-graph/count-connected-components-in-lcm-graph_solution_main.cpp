int main() {
    // Define 10 diverse test inputs
    vector<vector<int>> testNums = {
        {1},                                           // small, threshold = 1
        {2, 3, 4, 9, 6},                               // mixed small numbers
        {5, 5, 5, 5, 5},                               // duplicates
        {100, 200, 300},                               // all > threshold
        {1, 2, 3, 4, 5, 6},                            // consecutive
        {2, 3, 5, 7, 11, 13},                          // primes
        {4, 8, 12, 16, 20, 24, 28, 32},                // multiples
        {1, 2, 3},                                     // threshold = 0 edge
        {10000, 9999, 5000, 2500, 1250, 1, 2, 4, 8, 16}, // large threshold mix
        {}                                             // empty nums
    };
    vector<int> thresholds = {
        1,     // for test 1
        10,    // for test 2
        5,     // for test 3
        50,    // for test 4
        6,     // for test 5
        15,    // for test 6
        32,    // for test 7
        0,     // for test 8
        10000, // for test 9
        100    // for test 10
    };

    // Check we have exactly 10 test inputs
    if (testNums.size() != 10 || thresholds.size() != 10) {
        cerr << "Error: Need exactly 10 test inputs.\n";
        return 1;
    }

    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        Solution sol;
        for (size_t i = 0; i < testNums.size(); ++i) {
            // Call the function and accumulate the results
            checksum += sol.countComponents(testNums[i], thresholds[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}