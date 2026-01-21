int main() {
    // Define 10 diverse test inputs
    vector<vector<string>> tests;

    // 1) Empty input
    tests.push_back({});

    // 2) Single edge
    tests.push_back({"ab"});

    // 3) Simple chain
    tests.push_back({"ab", "bc", "cd", "de"});

    // 4) Branching from a with further dependencies
    tests.push_back({"ab", "ac", "ad", "be", "cf"});

    // 5) Multiple disconnected components
    tests.push_back({"ab", "cd", "ef", "gh"});

    // 6) Simple cycle
    tests.push_back({"ab", "bc", "ca"});

    // 7) Self-loops
    tests.push_back({"aa", "bb", "cc"});

    // 8) Duplicated edges and a cycle
    tests.push_back({"ab", "ab", "bc", "bc", "cd", "da"});

    // 9) Large 10-cycle
    tests.push_back({"ab", "bc", "cd", "de", "ef", "fg", "gh", "hi", "ij", "ja"});

    // 10) Mixed cycles and branches
    tests.push_back({"az", "zb", "bc", "cd", "de", "ea", "ay", "yx"});

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<string> words = tests[i];
            auto res = sol.supersequences(words);
            // Accumulate checksum based on results
            long long local = 0;
            for (const auto& vec : res) {
                for (int v : vec) local += v;
            }
            // Mix in test index and iteration to avoid trivial constant folding
            checksum += local * static_cast<long long>((i + 1) + (iter & 7));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}