int main() {
    std::vector<TestCase> tests = {
        {1, 1, 1},
        {1, 10, 7},
        {10, 1, 3},
        {3, 3, 5},
        {10, 10, 50},
        {45, 37, 800},
        {100, 100, 5000},
        {300, 500, 120000},
        {500, 300, 75000},
        {1000, 1000, 500000}
    };

    Solution solver;
    volatile long long checksum = 0; // volatile to further prevent optimization

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            int result = solver.findKthNumber(t.m, t.n, t.k);
            checksum += result;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}