int main() {
    // Define 10 diverse test inputs

    // 1) Single node
    vector<int> parent1 = {-1};
    string s1 = "a";

    // 2) Two-node chain
    vector<int> parent2 = {-1, 0};
    string s2 = "ab";

    // 3) Chain of 5
    vector<int> parent3 = {-1, 0, 1, 2, 3};
    string s3 = "abcde";

    // 4) Balanced binary tree with palindrome string
    vector<int> parent4 = {-1, 0, 0, 1, 1, 2, 2};
    string s4 = "racecar";

    // 5) Star tree of 10 nodes
    vector<int> parent5 = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    string s5 = "abcdefghij";

    // 6) Random-like tree n=50
    int n6 = 50;
    vector<int> parent6 = generateParent(n6);
    string s6 = generateString(n6);

    // 7) Random-like tree n=100
    int n7 = 100;
    vector<int> parent7 = generateParent(n7);
    string s7 = generateString(n7);

    // 8) Random-like tree n=300
    int n8 = 300;
    vector<int> parent8 = generateParent(n8);
    string s8 = generateString(n8);

    // 9) Random-like tree n=700
    int n9 = 700;
    vector<int> parent9 = generateParent(n9);
    string s9 = generateString(n9);

    // 10) Random-like tree n=1200
    int n10 = 1200;
    vector<int> parent10 = generateParent(n10);
    string s10 = generateString(n10);

    vector<vector<int>*> parents = {
        &parent1, &parent2, &parent3, &parent4, &parent5,
        &parent6, &parent7, &parent8, &parent9, &parent10
    };
    vector<string> strings = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10};

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < parents.size(); ++i) {
            vector<bool> res = sol.findAnswer(*parents[i], strings[i]);
            uint64_t local = 0;
            for (size_t j = 0; j < res.size(); ++j) {
                local += res[j] ? (j + 1) : 0;
            }
            // Mix in some per-test values to avoid trivial cancellation
            local ^= (uint64_t)res.size() * (i + 1);
            checksum += local;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed (ns): " << elapsed_ns << "\n";
    return 0;
}