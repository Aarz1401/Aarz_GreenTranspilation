int main() {
    vector<string> tests = {
        "",                 // empty
        "a",                // single char
        "aaaaaa",           // all same
        "ababababa",        // alternating
        "abcde",            // all distinct
        "aaabbbccc",        // grouped repeats
        "aba",              // palindrome
        "abcbaabcba",       // repeated palindrome segments
        "bacbacbacb",       // repeating pattern
        "zzzyxyzzxxyyzz"    // mixed repeats
    };

    Solution sol;
    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += sol.strangePrinter(s);
        }
    }

    auto end = high_resolution_clock::now();
    double elapsed_ms = duration_cast<duration<double, std::milli>>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed ms: " << elapsed_ms << "\n";

    return 0;
}