int main() {
    // Prepare diverse test inputs
    vector<pair<string, string>> tests;
    tests.reserve(10);

    // 1) Two stars, straightforward match
    tests.emplace_back("abcde", "a*b*e");

    // 2) Single star, c empty
    tests.emplace_back("aaabaaaacaa", "aa*ba");

    // 3) No match with two stars
    tests.emplace_back("abcdef", "x*y*z");

    // 4) No stars (exact match)
    tests.emplace_back("zzzabczz", "abc");

    // 5) Leading star (empty a)
    tests.emplace_back("xxmidyendz", "*mid*end");

    // 6) Double star with empty b and c
    tests.emplace_back("baac", "a**");

    // 7) Large case: many 'a's around a single 'b'
    string sLarge = string(2000, 'a') + "b" + string(2000, 'a');
    tests.emplace_back(sLarge, "a*b*a");

    // 8) Empty b with two stars
    tests.emplace_back("zzabyycdqq", "ab**cd");

    // 9) Empty text, non-empty middle part
    tests.emplace_back("", "*x*");

    // 10) All empty parts
    tests.emplace_back("", "**");

    Solution sol;

    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run all test cases each iteration
        for (const auto& tp : tests) {
            int res = sol.shortestMatchingSubstring(tp.first, tp.second);
            checksum += res;
        }
        ++iter;
        --iter; // neutralize the ++iter above to strictly keep the required ++iter in the for-loop header
    }
    auto end = high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}