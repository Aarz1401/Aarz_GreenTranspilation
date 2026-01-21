int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Prepare 10 diverse test inputs
    vector<pair<vector<string>, int>> tests;
    tests.reserve(10);

    // 1. Empty list
    tests.push_back({{}, 1});

    // 2. Single word
    tests.push_back({{"hello"}, 1});

    // 3. All same words
    tests.push_back({{"aaa", "aaa", "aaa", "aaa"}, 2});

    // 4. No common prefixes
    tests.push_back({{"dog", "cat", "bird", "fish"}, 2});

    // 5. Common prefixes among many
    tests.push_back({{"interview", "interval", "internal", "internet"}, 3});

    // 6. k equals n
    tests.push_back({{"alpha", "alpine", "altar", "altruist", "algebra"}, 5});

    // 7. k greater than n
    tests.push_back({{"abc", "abd"}, 3});

    // 8. Chain of prefixes
    tests.push_back({{"a", "ab", "abc", "abcd", "abcde"}, 4});

    // 9. Case sensitivity and ordering
    tests.push_back({{"Apple", "application", "app", "App", "apply"}, 2});

    // 10. Long strings
    {
        string x1000(1000, 'x');
        string a = x1000 + "a";
        string b = x1000 + "b";
        string c = string(999, 'x') + 'y';
        string d(1000, 'z');
        tests.push_back({{a, b, c, d}, 2});
    }

    Solution sol;
    long long checksum = 0;

    using hrc = std::chrono::high_resolution_clock;
    auto start = hrc::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            vector<int> res = sol.longestCommonPrefix(t.first, t.second);
            for (int v : res) checksum += v;
            checksum += static_cast<long long>(t.first.size() * 131 + t.second);
        }
    }

    auto end = hrc::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << duration_ns << "\n";

    return 0;
}