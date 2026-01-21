int main() {
    // 10 diverse test inputs for the racecar problem
    std::vector<int> tests = {
        1,   // minimal
        2,   // small
        3,   // 2^2 - 1
        4,   // power of two
        6,   // just below 7
        7,   // 2^3 - 1
        9,   // just above 8
        15,  // 2^4 - 1
        31,  // 2^5 - 1
        500  // larger target
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int t : tests) {
            checksum += sol.racecar(t);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = static_cast<double>(elapsed_ns) / 1e6;

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}