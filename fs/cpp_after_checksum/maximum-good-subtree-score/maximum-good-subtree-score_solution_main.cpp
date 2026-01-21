int main() {
    // Define 10 diverse single-node test cases to keep benchmark efficient
    vector<TestCase> tests;
    tests.push_back({{7}, {0}});               // single digit
    tests.push_back({{0}, {0}});               // zero value
    tests.push_back({{11}, {0}});              // repeated digit (invalid mask)
    tests.push_back({{98}, {0}});              // two unique digits
    tests.push_back({{101}, {0}});             // repeated digit (invalid mask)
    tests.push_back({{1234}, {0}});            // multiple unique digits
    tests.push_back({{1000000000}, {0}});      // many repeated zeros (invalid mask)
    tests.push_back({{24680}, {0}});           // even digits including zero
    tests.push_back({{13579}, {0}});           // odd digits
    tests.push_back({{987654321}, {0}});       // long unique digits

    Solution sol;

    volatile long long checksum = 0;

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::microseconds;

    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.goodSubtreeSum(const_cast<vector<int>&>(tc.vals),
                                           const_cast<vector<int>&>(tc.par));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed << "\n";

    return 0;
}