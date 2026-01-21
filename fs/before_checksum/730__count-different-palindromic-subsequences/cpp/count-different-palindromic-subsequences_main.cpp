int main() {
    vector<string> tests = {
        "",
        "a",
        "aa",
        "ab",
        "abcd",
        "dcba",
        "aaaabbbbccccdddd",
        "ababababcdcdcdcd",
        "abccbaabccba",
        "dacabadacabadacaba"
    };

    Solution sol;
    uint64_t checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += static_cast<uint64_t>(sol.countPalindromicSubsequences(s));
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}