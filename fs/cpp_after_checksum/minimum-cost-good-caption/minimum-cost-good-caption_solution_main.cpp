int main() {
    // Define 10 diverse test inputs (strings as required by the solution)
    vector<string> tests = {
        "",    // empty
        "a",   // single lowercase
        "z",   // single lowercase end
        "A",   // single uppercase
        "ab",  // two lowercase ascending
        "ba",  // two lowercase descending
        "zz",  // two same end chars
        "aa",  // two same start chars
        "Az",  // mixed case
        "mm"   // two middle letters
    };

    Solution sol;
    uint64_t checksum = 0;

    using clock_type = std::chrono::high_resolution_clock;
    auto start = clock_type::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            string out = sol.minCostGoodCaption(tests[i]);
            // Mix output into checksum
            checksum += static_cast<uint64_t>(out.size());
            for (char c : out) {
                checksum = checksum * 1315423911u + static_cast<unsigned char>(c);
            }
            // Also mix input to avoid trivial zero checksum
            checksum += static_cast<uint64_t>(tests[i].size());
            if (!tests[i].empty()) {
                checksum ^= static_cast<uint64_t>(static_cast<unsigned char>(tests[i][0]));
            }
        }
    }

    auto end = clock_type::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";
    return 0;
}