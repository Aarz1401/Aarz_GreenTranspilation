int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<int>> numsList = {
        {1, 2, 3, 4},                // Case 1: simple positives
        {5},                         // Case 2: single element
        {0, 0, 5},                   // Case 3: includes zeros
        {5, -2, 7, -3},              // Case 4: includes negatives
        {2, 2, 2, 2, 2},             // Case 5: duplicates
        {3, 3, 3, 3},                // Case 6: duplicates length 4
        {1000, 1000},                // Case 7: large values to trigger cap
        {9, 8, 7},                   // Case 8: small with known alt sum 1
        {0, 5, 0, 5},                // Case 9: zeros interleaved
        {1, 1, 2, 3, 5, 8, 13, 21}   // Case 10: Fibonacci-like
    };

    vector<int> ks = {
        3,    // Case 1 target (subseq [2,3,4] -> 2-3+4=3)
        5,    // Case 2 target ([5])
        5,    // Case 3 target ([5] or [0,0,5])
        7,    // Case 4 target ([7] or [5,-2])
        2,    // Case 5 target (odd-length subseqs or single)
        0,    // Case 6 target (even-length subseqs)
        0,    // Case 7 target ([1000,1000] -> 0)
        1,    // Case 8 target ([9,8] -> 1)
        0,    // Case 9 target ([0] subseqs)
        6     // Case 10 target ([3,5,8] -> 3-5+8=6)
    };

    vector<int> limits = {
        100,       // Case 1 limit
        10,        // Case 2 limit
        1000,      // Case 3 limit
        1000,      // Case 4 limit
        100,       // Case 5 limit
        100,       // Case 6 limit
        500000,    // Case 7 limit to trigger cap
        1000000,   // Case 8 limit
        10,        // Case 9 limit
        1000       // Case 10 limit
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code here
        for (int i = 0; i < 10; ++i) {
            int res = sol.maxProduct(numsList[i], ks[i], limits[i]);
            checksum += res;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}