int main() {
    // 10 diverse test inputs for the Solution::specialPalindrome method
    const vector<long long> tests = {
        -1LL,                      // negative input
        0LL,                       // zero
        1LL,                       // already a palindrome
        2LL,                       // small non-pal
        21LL,                      // between palindromes
        22LL,                      // exact palindrome
        12345LL,                   // mid-range
        987654321012345LL,         // 15-digit
        8999999999999999LL,        // large 16-digit near boundary
        9223372036854775LL         // very large 16-digit
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            long long res = sol.specialPalindrome(tests[i]);
            // mix in iter and index to avoid predictable sums
            checksum += static_cast<unsigned long long>(res) ^ (static_cast<unsigned long long>(iter) << (i % 17));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}