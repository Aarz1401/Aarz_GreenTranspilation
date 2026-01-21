int main() {
    Solution sol;

    const std::vector<TestCase> tests = {
        {1, 2, 3},                      // simple small values
        {5, 2, 4},                      // one multiple of the other
        {10, 5, 5},                     // equal A and B
        {100, 3, 7},                    // coprime small
        {1000, 8, 12},                  // gcd > 1
        {100000, 1, 1000000000},        // A = 1
        {1000000, 999999937, 999999929},// large primes near 1e9
        {200000000, 40000, 39999},      // mid-large, near-coprime
        {1000000000, 2147483647, 2147483646}, // near int max
        {123456789, 12345, 67890}       // arbitrary mixed
    };

    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int res = sol.nthMagicalNumber(tests[i].N, tests[i].A, tests[i].B);
            checksum += res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}