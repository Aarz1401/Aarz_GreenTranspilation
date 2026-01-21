int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    tests.push_back({{1}, {1}});                                               // Case 1: trivial
    tests.push_back({{2, 3, 4}, {2, 3}});                                      // Case 2: small mix
    tests.push_back({{5, 7, 11}, {6, 10, 15}});                                // Case 3: co-prime targets
    tests.push_back({{8, 16, 24, 40}, {4, 8, 2, 4}});                          // Case 4: duplicates in target
    tests.push_back({{1000000000, 999999937, 500000003}, {97, 89, 83, 79}});   // Case 5: large numbers/primes
    tests.push_back({{12, 18, 30, 42, 60}, {6, 12, 18, 24, 30}});              // Case 6: increasing multiples
    tests.push_back({{1,2,3,4,5,6,7,8,9,10}, {2,3,5,7,11}});                   // Case 7: more nums, 5 targets
    tests.push_back({{0, 0, 0}, {0, 1, 2}});                                   // Case 8: includes zeroes
    tests.push_back({{123, 456, 789, 101112}, {9, 12, 27, 36}});               // Case 9: composite targets
    tests.push_back({{13, 26, 39, 52, 65, 78}, {13, 26, 52, 104}});            // Case 10: powers/multiples

    Solution sol;
    long long checksum = 0;

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::microseconds;

    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.minimumIncrements(tc.nums, tc.target);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}