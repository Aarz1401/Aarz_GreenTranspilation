int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<string, string>> tests = {
        {"0", "0"},
        {"1", "1"},
        {"1", "2"},
        {"4", "4"},
        {"1", "1000"},
        {"100", "1000"},
        {"5", "6"},
        {"400000000000000", "900000000000000"},
        {"1", "99999999999999"},
        {"4000000000000000", "5000000000000000"}
    };

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& pr : tests) {
            checksum += sol.superpalindromesInRange(pr.first, pr.second);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> elapsed = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}