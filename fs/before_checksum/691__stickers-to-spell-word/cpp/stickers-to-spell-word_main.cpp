int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<vector<string>, string>> tests;
    tests.reserve(10);
    tests.emplace_back(vector<string>{"with","example","science"}, "thehat");
    tests.emplace_back(vector<string>{"notice","possible"}, "basicbasic");
    tests.emplace_back(vector<string>{"these","guess","about","garden","him"}, "atomher");
    tests.emplace_back(vector<string>{"a","b","c"}, "abccba");
    tests.emplace_back(vector<string>{"ab","bc","ca"}, "abccab");
    tests.emplace_back(vector<string>{"aaaa","b","c","d"}, "aaaaa");
    tests.emplace_back(vector<string>{"abc","abd","acd","bcd"}, "abcd");
    tests.emplace_back(vector<string>{"with","out","input","stickers"}, "withoutstickers");
    tests.emplace_back(vector<string>{"the","quick","brown","fox","jumps","over","lazy","dog"}, "thequickbrownfox");
    tests.emplace_back(vector<string>{"abc","def"}, "");

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            auto& stickers = tests[i].first;
            auto& target = tests[i].second;
            int res = sol.minStickers(stickers, target);
            checksum += static_cast<long long>(res) * static_cast<long long>(i + 1);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}