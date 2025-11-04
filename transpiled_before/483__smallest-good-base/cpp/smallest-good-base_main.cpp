int main() {
    // Define 10 diverse test inputs as strings (as required by the solution)
    vector<string> tests = {
        "3",                        // small, 2^2 - 1
        "13",                       // 1 + 3 + 9
        "31",                       // 2^5 - 1
        "4681",                     // 1 + 8 + 8^2 + 8^3 + 8^4
        "121",                      // 1 + 10 + 100
        "21",                       // 1 + 4 + 16
        "1000000000000000000",      // large 1e18
        "999999999999999999",       // large, 18-digit 9s
        "2251799813685247",         // 2^51 - 1
        "1099511627775"             // 2^40 - 1
    };

    Solution sol;
    uint64_t checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            string res = sol.smallestGoodBase(tests[i]);
            // Accumulate into checksum to prevent optimization
            uint64_t b = stoull(res);
            checksum += b;
            checksum ^= (static_cast<uint64_t>(res.size()) + static_cast<uint64_t>(i) + static_cast<uint64_t>(iter));
            checksum = (checksum << 7) | (checksum >> (64 - 7)); // simple bit mix
        }
    }

    auto end = Clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << '\n';
    cout << "Elapsed time (ns): " << elapsed_ns << '\n';
    return 0;
}