int main() {
    // Prepare 10 diverse test inputs
    vector<string> tests;
    tests.reserve(10);

    // 1. Empty string
    tests.emplace_back("");

    // 2. Single character
    tests.emplace_back("a");

    // 3. Already a palindrome with mixed repeated chars
    tests.emplace_back("aaabaaa");

    // 4. No palindromic prefix beyond first char
    tests.emplace_back("abcd");

    // 5. Typical example from problem statements
    tests.emplace_back("aacecaaa");

    // 6. Classic palindrome
    tests.emplace_back("racecar");

    // 7. Repeated pattern not a palindrome
    tests.emplace_back("abababab");

    // 8. Near-palindromic odd length
    tests.emplace_back("xyzzy");

    // 9. Medium-long mixed sequence
    {
        string t;
        t.reserve(2048);
        for (int i = 0; i < 2048; ++i) {
            t.push_back(static_cast<char>('a' + (i % 26)));
        }
        tests.emplace_back(std::move(t));
    }

    // 10. Long string with large palindromic prefix potential
    {
        string t;
        t.reserve(4096);
        for (int i = 0; i < 2000; ++i) t.push_back(static_cast<char>('z' - (i % 26)));
        t += "MIXED_case_12345!";
        for (int i = 1999; i >= 0; --i) t.push_back(static_cast<char>('z' - (i % 26)));
        tests.emplace_back(std::move(t));
    }

    Solution sol;
    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            string res = sol.shortestPalindrome(s);
            checksum ^= static_cast<unsigned long long>(res.size());
            if (!res.empty()) {
                checksum ^= static_cast<unsigned long long>(static_cast<unsigned char>(res.front())) << 1;
                checksum ^= static_cast<unsigned long long>(static_cast<unsigned char>(res.back())) << 2;
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}