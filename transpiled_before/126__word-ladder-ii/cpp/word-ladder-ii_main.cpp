int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    // 1) Classic example with two shortest ladders
    tests.push_back(TestCase{
        "hit", "cog",
        {"hot","dot","dog","lot","log","cog"}
    });

    // 2) End word missing -> no path
    tests.push_back(TestCase{
        "hit", "cog",
        {"hot","dot","dog","lot","log"}
    });

    // 3) Expanded dictionary to create more branching
    tests.push_back(TestCase{
        "hit", "cog",
        {"hot","dot","dog","lot","log","cog","hig","hog","cot","cig","cit"}
    });

    // 4) Single-letter words
    tests.push_back(TestCase{
        "a", "c",
        {"a","b","c"}
    });

    // 5) Direct transformation available with distractors
    tests.push_back(TestCase{
        "bat", "cat",
        {"bot","bog","cog","cot","cat","cab","car","bar","bat"}
    });

    // 6) 4-letter path with a clear chain
    tests.push_back(TestCase{
        "lost", "miss",
        {"most","mist","miss","lost","fist","fish"}
    });

    // 7) 4-letter with stepwise bridging
    tests.push_back(TestCase{
        "aaaa", "bbbb",
        {"aaab","aabb","abbb","bbbb","bbba"}
    });

    // 8) Well-known 4-letter ladder
    tests.push_back(TestCase{
        "lead", "gold",
        {"load","goad","gold","lead","mead"}
    });

    // 9) Empty word list -> no path
    tests.push_back(TestCase{
        "a", "b",
        {}
    });

    // 10) No neighbors from begin; end present but unreachable
    tests.push_back(TestCase{
        "zzz", "aaa",
        {"aaa","abc","abd","aac","acc"}
    });

    Solution solver;

    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<string> wl = tc.wordList; // copy to avoid any accidental aliasing effects
            auto res = solver.findLadders(tc.begin, tc.end, wl);

            // Accumulate a checksum from the results
            checksum += static_cast<uint64_t>(res.size());
            for (const auto& path : res) {
                checksum ^= static_cast<uint64_t>(path.size()) * 1315423911ull;
                for (const auto& w : path) {
                    for (unsigned char ch : w) {
                        checksum = (checksum * 1315423911ull) ^ ch ^ 0x9e3779b97f4a7c15ull;
                    }
                }
            }
            // Mix in begin/end sizes to avoid empty-result cases being optimized out
            checksum ^= (static_cast<uint64_t>(tc.begin.size()) << 32) ^ static_cast<uint64_t>(tc.end.size());
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}