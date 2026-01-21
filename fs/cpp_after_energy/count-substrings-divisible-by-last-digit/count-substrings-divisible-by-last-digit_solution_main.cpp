int main() {
    // Prepare 10 diverse test inputs (strings of digits)
    vector<string> tests;
    tests.reserve(10);
    tests.push_back("");                                   // 1) empty
    tests.push_back("0");                                  // 2) single zero
    tests.push_back("9");                                  // 3) single nine
    tests.push_back("27");                                 // 4) small mixed digits
    tests.push_back("1234567890");                         // 5) all digits once
    tests.push_back(string(100, '7'));                     // 6) many 7s
    tests.push_back(repeatPattern("31415926", 32));        // 7) length 256
    tests.push_back(repeatPattern("0123456789", 100));     // 8) length 1000
    tests.push_back(genLCGDigits(2000, 123456789u));       // 9) length 2000 pseudo-random digits
    tests.push_back(string(4096, '8'));                    // 10) many 8s

    Solution sol;

    volatile long long checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            long long ans = sol.countSubstrings(s);
            checksum += ans;
        }
    }

    auto end = Clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}