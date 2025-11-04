int main() {
    vector<pair<string, string>> tests = {
        {"abc", "ababc"},
        {"abca", "aabcaca"},
        {"a", "aaaaaa"},
        {"aa", "aaaa"},
        {"xyz", "xyzxyz"},
        {"aba", "ababa"},
        {"abc", "abcabcabc"},
        {"ab", "abab"},
        {"z", "zzzzz"},
        {"abc", "defgh"}
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            const string& stamp = tests[i].first;
            const string& target = tests[i].second;
            vector<int> res = sol.movesToStamp(stamp, target);
            checksum += res.size();
            for (int v : res) {
                checksum ^= (static_cast<unsigned long long>(v + 1) * 1315423911ull);
                checksum += (stamp.size() << 3) + (target.size() << 1) + v;
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time: " << elapsed_us << " us\n";
    return 0;
}