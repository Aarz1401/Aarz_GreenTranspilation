int main() {
    // Define 10 diverse test inputs for the solution
    const std::array<int, 10> inputs = {0, 1, 2, 3, 4, 5, 10, 50, 100, 5000};

    Solution sol;
    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : inputs) {
            checksum += sol.checkRecord(n);
        }
    }

    auto end = clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}