int main() {
    std::vector<std::pair<int, int>> tests = {
        {1, 1},
        {1, 1000},
        {2, 100},
        {2, 10000},
        {3, 1000},
        {10, 10000},
        {15, 1000000},
        {50, 1000000},
        {100, 10000000},
        {3, 2000000000}
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int K = tests[i].first;
            int N = tests[i].second;
            int res = sol.superEggDrop(K, N);
            checksum += (res ^ (static_cast<int>(i) + 31) ^ (iter << 1)) + K + (N & 0xFFFF);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}