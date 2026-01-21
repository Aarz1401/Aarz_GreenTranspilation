int main() {
    // Define 10 diverse test inputs (n, k)
    vector<pair<long long, int>> tests = {
        {1LL, 0},
        {1LL, 1},
        {1000000000000000LL, 2},
        {999999999999999LL, 3},
        {(1LL << 49), 1},
        {(1LL << 49) + 1234567890123LL, 4},
        {(1LL << 20) - 1, 5},
        {(1LL << 40) + (1LL << 20) + 12345LL, 2},
        {123456789LL, 3},
        {500000000000000LL, 6}
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tk : tests) {
            checksum += sol.popcountDepth(tk.first, tk.second);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}