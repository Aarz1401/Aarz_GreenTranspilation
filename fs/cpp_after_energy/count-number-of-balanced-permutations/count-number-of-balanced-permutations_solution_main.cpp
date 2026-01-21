int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse test inputs (strings of digits as required by the solution)
    vector<string> tests;
    tests.reserve(10);
    tests.push_back("0");                          // trivial, sum=0
    tests.push_back("12");                         // small even length
    tests.push_back("123");                        // odd length
    tests.push_back("00112233");                   // repeats with zeros
    tests.push_back("999999");                     // all same, large digit
    tests.push_back("3141592653");                 // mixed digits length 10
    tests.push_back("55555");                      // odd sum -> immediate 0
    tests.push_back("9876543210");                 // digits 0..9 sum odd -> 0
    tests.push_back("1111111111");                 // many ones
    tests.push_back("00000000000000000000");       // many zeros

    Solution sol;
    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code here
        for (const auto& s : tests) {
            int ans = sol.countBalancedPermutations(s);
            checksum = (checksum * 1315423911ULL + static_cast<unsigned long long>(ans)) ^ 0x9e3779b97f4a7c15ULL;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    double elapsed_ms = chrono::duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed(ms): " << elapsed_ms << "\n";
    return 0;
}