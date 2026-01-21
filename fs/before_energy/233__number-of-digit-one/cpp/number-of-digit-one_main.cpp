int main() {
    // 10 diverse test inputs for the countDigitOne function
    std::vector<int> testInputs = {
        0,              // edge case: zero
        1,              // minimal positive
        9,              // single digit max
        10,             // transition to two digits
        11,             // multiple ones
        19,             // teen boundary
        20,             // no ones in tens place
        99,             // just before 100
        1000000,        // large power-of-10 boundary
        2000000000      // very large within int range
    };

    Solution solver;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : testInputs) {
            checksum += solver.countDigitOne(n);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}