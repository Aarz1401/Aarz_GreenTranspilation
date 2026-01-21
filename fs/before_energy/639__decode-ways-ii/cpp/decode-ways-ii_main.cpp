int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> tests;
    tests.emplace_back("12");           // simple digits
    tests.emplace_back("*");            // single wildcard
    tests.emplace_back("1*");           // '1' followed by wildcard
    tests.emplace_back("2*");           // '2' followed by wildcard
    tests.emplace_back("**");           // double wildcard
    tests.emplace_back("0");            // invalid single zero
    tests.emplace_back("10*");          // zero handling with valid prefix
    tests.emplace_back("26*");          // boundary with '2' and wildcard
    tests.emplace_back("230");          // invalid zero after '3'
    tests.emplace_back(string(100, '*'));// long all-wildcards

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += sol.numDecodings(s);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}