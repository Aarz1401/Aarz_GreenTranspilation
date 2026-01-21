int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1: Empty string, t=0, empty nums
    tests.push_back({"", 0, {}});

    // Test 2: Single character, minimal nums
    tests.push_back({"a", 1, {1}});

    // Test 3: Small string, simple transitions
    tests.push_back({"abc", 2, {1, 1, 1}});

    // Test 4: Repeated 'z', sparse matrix across full alphabet
    {
        vector<int> nums4(26);
        for (int i = 0; i < 26; ++i) nums4[i] = i % 3; // 0,1,2 repeating
        tests.push_back({string(10, 'z'), 3, nums4});
    }

    // Test 5: Large counts for 'a', limited transitions
    {
        vector<int> nums5(26, 0);
        nums5[0] = 2; // 'a' -> 'b','c'
        nums5[1] = 1; // 'b' -> 'c'
        tests.push_back({string(1000, 'a'), 8, nums5});
    }

    // Test 6: Partial nums vector smaller than 26
    tests.push_back({"leetcode", 5, {2, 0, 1, 2, 1}});

    // Test 7: Full alphabet string, sparse transitions across all rows
    {
        vector<int> nums7(26);
        for (int i = 0; i < 26; ++i) nums7[i] = (i % 3); // 0,1,2 repeating
        tests.push_back({"abcdefghijklmnopqrstuvwxyz", 7, nums7});
    }

    // Test 8: Very sparse transitions, larger t
    {
        vector<int> nums8(26, 0);
        nums8[0] = 1;  // 'a' -> 'b'
        nums8[1] = 2;  // 'b' -> 'c','d'
        nums8[12] = 1; // 'm' -> 'n'
        nums8[23] = 2; // 'x' -> 'y','z'
        tests.push_back({"abbaabbaab", 16, nums8});
    }

    // Test 9: Long string, nums longer than 26 (extra ignored)
    {
        string base9 = "thequickbrownfoxjumpsoverthelazydog";
        string s9;
        for (int i = 0; i < 6; ++i) s9 += base9; // length ~ 210
        vector<int> nums9(30);
        for (int i = 0; i < 30; ++i) nums9[i] = (i * 7) % 3; // 0,1,2 pattern
        tests.push_back({s9, 12, nums9});
    }

    // Test 10: No transitions (empty nums), t=1
    tests.push_back({"mismatchcases", 1, {}});

    Solution sol;
    volatile uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            int res = sol.lengthAfterTransformations(tc.s, tc.t, tc.nums);
            checksum = (checksum * 1315423911ull) ^ static_cast<uint64_t>(res + 0x9e3779b97f4a7c15ull);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << static_cast<uint64_t>(checksum) << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}