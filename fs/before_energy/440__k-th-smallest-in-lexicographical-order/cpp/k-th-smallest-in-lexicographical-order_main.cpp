int main() {
    Solution solver;

    // 10 diverse test inputs (n, k)
    std::vector<std::pair<int, int>> tests = {
        {1, 1},
        {13, 2},
        {1000, 1},
        {1000, 1000},
        {999999937, 123456789},
        {1000000000, 1000000000},
        {500000000, 250000000},
        {10, 10},
        {271828182, 31415926},
        {987654321, 87654321}
    };

    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        long long local_sum = 0;
        for (const auto& tc : tests) {
            local_sum += solver.findKthNumber(tc.first, tc.second);
        }
        checksum += local_sum;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << std::endl;
    std::cout << "Elapsed time (ns): " << elapsed_ns << std::endl;

    return 0;
}