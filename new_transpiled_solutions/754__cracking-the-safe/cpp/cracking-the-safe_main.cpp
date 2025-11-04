int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse (n, k) test cases
    vector<pair<int,int>> tests = {
        {1, 1},
        {1, 2},
        {1, 10},
        {2, 2},
        {2, 3},
        {2, 10},
        {3, 2},
        {3, 3},
        {3, 5},
        {4, 2}
    };

    Solution sol;
    uint64_t checksum = 0;
    uint64_t total_len = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tk : tests) {
            string res = sol.crackSafe(tk.first, tk.second);
            total_len += static_cast<uint64_t>(res.size());
            // FNV-1a 64-bit per-result to prevent optimization
            uint64_t h = 1469598103934665603ULL;
            for (unsigned char c : res) {
                h ^= c;
                h *= 1099511628211ULL;
            }
            // Mix in size and iteration to vary checksum
            h ^= static_cast<uint64_t>(res.size()) + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
            checksum ^= h ^ (static_cast<uint64_t>(iter) * 0x9e3779b97f4a7c15ULL);
        }
    }

    auto end = clock::now();
    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << " TotalLength: " << total_len << " Elapsed(ms): " << elapsed_ms << "\n";
    return 0;
}