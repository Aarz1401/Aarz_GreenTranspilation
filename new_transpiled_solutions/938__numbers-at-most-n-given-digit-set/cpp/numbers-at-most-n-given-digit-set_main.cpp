int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;
    tests.push_back({{"1","3","5","7"}, 100});              // typical example
    tests.push_back({{"1","4","9"}, 1000000000});           // large N, small digit set
    tests.push_back({{"7"}, 8});                            // single digit set
    tests.push_back({{"2","3","5","7"}, 29});               // primes as digits
    tests.push_back({{"1","2","3","4","5","6","7","8","9"}, 999999999}); // many digits, large N
    tests.push_back({{"0","1","2"}, 100});                  // includes zero
    tests.push_back({{"8","9"}, 1000});                     // two high digits
    tests.push_back({{"1"}, 111111});                       // repetitive N with single digit
    tests.push_back({{"3","4","8"}, 3456});                 // mixed mid-range
    tests.push_back({{}, 12345});                           // empty digit set (edge case)

    Solution sol;

    volatile long long checksum_sink = 0; // to avoid optimization
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.atMostNGivenDigitSet(tc.D, tc.N);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    checksum_sink = checksum;

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum_sink << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}