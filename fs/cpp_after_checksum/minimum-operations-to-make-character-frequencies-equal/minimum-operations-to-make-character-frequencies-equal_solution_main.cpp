int main() {
    // Prepare 10 diverse test inputs (strings as required by the solution)
    vector<string> tests;
    tests.push_back(""); // 1. empty
    tests.push_back("a"); // 2. single char
    tests.push_back("aaaaaaa"); // 3. uniform
    tests.push_back("abc"); // 4. small distinct
    tests.push_back("abababababababababababab"); // 5. alternating pattern
    tests.push_back("thequickbrownfoxjumpsoveralazydog"); // 6. pangram
    tests.push_back("mississippi"); // 7. repeated clusters
    {
        string t8;
        for (char c = 'a'; c <= 'z'; ++c) t8.push_back(c);
        tests.push_back(t8); // 8. full alphabet once
    }
    {
        string t9;
        t9.append(500, 'a');
        t9.append(500, 'b');
        tests.push_back(t9); // 9. large two-char block
    }
    {
        string t10;
        for (int k = 0; k < 100; ++k) t10 += "leetcode";
        tests.push_back(t10); // 10. repeated word
    }

    Solution sol;
    long long checksum = 0;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += sol.makeStringGood(s);
        }
    }

    auto end = high_resolution_clock::now();
    double elapsed_ms = duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}