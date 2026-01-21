int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs: pairs of decimal strings (l, r) and base b
    const vector<tuple<string, string, int>> tests = {
        {"0", "0", 2},                                                    // exact zero in base 2
        {"0000", "0000", 3},                                              // leading zeros, zero range
        {"0", "9", 10},                                                   // small range in base 10
        {"10", "99", 10},                                                 // two-digit range in base 10
        {"1", "100000", 2},                                               // larger range in base 2
        {"12345678901234567890", "12345678901234567999", 10},             // big numbers in base 10
        {"999999999999999999", "1000000000000000000", 16},                // boundary around 1e18 in base 16
        {"123456789", "987654321", 7},                                    // mid-size range in base 7
        {"42", "42", 36},                                                 // single value in base 36
        {"10000000000000000000000000000000000000000000000000",
         "10000000000000000000000000000000000000000000012345", 11}        // very large numbers in base 11
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            const string& l = get<0>(t);
            const string& r = get<1>(t);
            int b = get<2>(t);
            int res = sol.countNumbers(l, r, b);
            // Mix into checksum to prevent optimization
            checksum ^= (static_cast<unsigned long long>(res) + 0x9e3779b97f4a7c15ULL + (checksum << 6) + (checksum >> 2));
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}