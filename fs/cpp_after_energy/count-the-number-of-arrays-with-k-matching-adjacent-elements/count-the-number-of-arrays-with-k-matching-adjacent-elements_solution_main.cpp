int main() {
    // Define 10 diverse test inputs (n, m, k)
    vector<tuple<int, int, int>> tests = {
        {1, 1, 0},            // minimal case
        {5, 3, 2},            // small typical
        {10, 1000, 0},        // k = 0
        {50, 2, 49},          // k = n - 1
        {1000, 1000000000, 500}, // large m, medium n
        {200000, 100000, 100000}, // large n
        {2, 1000000007, 1},   // m = MOD
        {100000, 1, 0},       // m = 1
        {3, 2, 1},            // small mixed
        {7, 5, 7}             // k > n - 1 -> zero combinations
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            int n, m, k;
            tie(n, m, k) = t;
            int res = sol.countGoodArrays(n, m, k);
            // Mix into checksum to avoid optimization
            checksum ^= (static_cast<unsigned long long>(res) + 0x9e3779b97f4a7c15ULL + (checksum << 6) + (checksum >> 2));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}