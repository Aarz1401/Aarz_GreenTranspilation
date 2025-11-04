int main() {
    vector<pair<string, int>> tests = {
        {"123", 6},
        {"232", 8},
        {"105", 5},
        {"00", 0},
        {"00", 1},
        {"3456", 21},
        {"9999", 100},
        {"12345", 15},
        {"1005", 5},
        {"214", 9}
    };

    Solution sol;
    size_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            auto res = sol.addOperators(tc.first, tc.second);
            checksum += res.size();
            for (const auto& s : res) {
                checksum += s.size();
                if (!s.empty()) checksum += static_cast<unsigned char>(s[0]);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}