int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<pair<string, string>> tests = {
        {"FFFFF", "ab"},                 // Mostly F, simple pattern
        {"TTTT", "aba"},                 // Overlapping T's that likely conflict (expected failure)
        {"TTTFFFF", "aaa"},              // Overlapping T's with compatible pattern
        {"FFTFFTF", "aba"},              // Mixed constraints
        {"", "abc"},                     // Empty str1
        {"T", "b"},                      // Single T and single-letter str2
        {"FTFTFTFTFT", "b"},             // Alternating constraints with m=1
        {"FFFFFFFF", "a"},               // All F with m=1
        {"TT", "ababa"},                 // Conflicting overlaps (expected failure)
        {"TFFTTFTFTFTTFTFFFTFTTTFTFF", "aababa"} // Larger mixed case
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            string res = sol.generateString(tc.first, tc.second);
            // Update checksum to avoid optimization
            // Simple mixing of size and few characters
            checksum ^= static_cast<unsigned long long>(res.size()) + 0x9e3779b97f4a7c15ULL + (checksum << 6) + (checksum >> 2);
            if (!res.empty()) {
                checksum += static_cast<unsigned long long>(static_cast<unsigned char>(res[0]));
                checksum += static_cast<unsigned long long>(static_cast<unsigned char>(res.back()));
            } else {
                checksum += 1ULL; // distinguish empty results
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}