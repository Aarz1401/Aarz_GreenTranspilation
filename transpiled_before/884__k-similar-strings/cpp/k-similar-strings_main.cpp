int main() {
    using namespace std;
    using namespace std::chrono;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs (pairs of anagram strings)
    vector<pair<string, string>> tests = {
        {"ab", "ab"},          // identical strings
        {"ab", "ba"},          // single swap needed
        {"aabc", "abca"},      // duplicates with small length
        {"abc", "bca"},        // rotation-like
        {"aabb", "bbaa"},      // duplicates reversed
        {"abac", "baca"},      // mixed duplicates
        {"abcdef", "fabcde"},  // longer permutation
        {"aabbcc", "ccbbaa"},  // more duplicates
        {"a", "a"},            // minimal length
        {"abcde", "abced"}     // near-sorted with a swap near the end
    };

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& p : tests) {
            checksum += sol.kSimilarity(p.first, p.second);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ms = duration_cast<duration<double, std::milli>>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}