int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<string>> tests;
    tests.reserve(10);

    // 1. Simple overlap
    tests.push_back({"ab", "bc"});

    // 2. No overlaps
    tests.push_back({"abc", "def", "ghi"});

    // 3. Classic multi-overlap case
    tests.push_back({"catgc", "ctaagt", "gcta", "ttca", "atgcatc"});

    // 4. Contains substrings
    tests.push_back({"abcd", "bc", "c", "d"});

    // 5. Duplicates and repeats
    tests.push_back({"aaa", "aaa", "aa"});

    // 6. Mixed with embedded word
    tests.push_back({"leetc", "code", "leetcode", "etco"});

    // 7. Circular overlaps
    tests.push_back({"abc", "bca", "cab"});

    // 8. Many similar strings
    tests.push_back({"aaaaa", "aaaa", "aaa", "aa", "a"});

    // 9. Longer strings with patterned overlaps
    {
        vector<string> t9;
        string t9a(200, 'a'); t9a += 'b'; t9a += string(200, 'c');
        string t9b(150, 'a'); t9b += "bc"; t9b += string(150, 'c');
        string t9c = string(200, 'c') + "d" + string(100, 'e');
        string t9d = string(100, 'a') + string(100, 'b') + string(100, 'c');
        string t9e = string(50, 'b') + string(200, 'c') + 'd';
        t9.push_back(t9a);
        t9.push_back(t9b);
        t9.push_back(t9c);
        t9.push_back(t9d);
        t9.push_back(t9e);
        tests.push_back(std::move(t9));
    }

    // 10. Mixed genome-like overlaps
    tests.push_back({"gttac", "tacga", "acg", "cgat", "gattt"});

    Solution sol;
    unsigned long long checksum = 0;

    const int iterations = 1;
    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            string res = sol.shortestSuperstring(tests[i]);
            // Simple rolling checksum to prevent optimization
            checksum ^= static_cast<unsigned long long>(res.size());
            if (!res.empty()) {
                checksum = (checksum * 1315423911ULL) ^ static_cast<unsigned long long>(static_cast<unsigned char>(res.front()));
                checksum = (checksum * 2654435761ULL) ^ static_cast<unsigned long long>(static_cast<unsigned char>(res.back()));
            }
            // Mix in a few characters across the string
            if (res.size() > 4) {
                checksum ^= static_cast<unsigned long long>(static_cast<unsigned char>(res[res.size() / 2]));
                checksum ^= static_cast<unsigned long long>(static_cast<unsigned char>(res[res.size() / 3]));
                checksum ^= static_cast<unsigned long long>(static_cast<unsigned char>(res[res.size() / 4]));
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}