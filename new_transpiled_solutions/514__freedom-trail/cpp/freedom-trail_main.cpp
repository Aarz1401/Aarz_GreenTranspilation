int main() {
    vector<pair<string, string>> tests = {
        {"godding", "gd"},
        {"abcde", "ade"},
        {"aaaaa", "aaaaa"},
        {"abcdefghijklmnopqrstuvwxyz", "leetcode"},
        {"ababcababc", "cabba"},
        {"xyz", ""},
        {"zxyxzx", "xzxyzxz"},
        {"a", "aaaaaaa"},
        {"qwertyuiopasdfghjklzxcvbnmqwertyuiop", "pazbycqdxre"},
        {"aaaabaaaacaaaadaaaae", "edcba"}
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int res = sol.findRotateSteps(tests[i].first, tests[i].second);
            checksum += res + static_cast<int>(i) + iter;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = elapsed_ns / 1e6;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}