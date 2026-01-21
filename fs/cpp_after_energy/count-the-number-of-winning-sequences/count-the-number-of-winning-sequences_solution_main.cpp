int main() {
    // Prepare 10 diverse test inputs (strings for this solution)
    vector<string> tests;
    tests.reserve(10);

    // 1) Empty
    tests.push_back("");

    // 2) Single char
    tests.push_back("F");

    // 3) Two chars
    tests.push_back("FW");

    // 4) Three chars
    tests.push_back("FWE");

    // 5) Mixed small
    tests.push_back("FFWEW"); // length 5

    // 6) Repeating pattern length 8
    tests.push_back("FWEFWEFW"); // length 8

    // 7) Balanced blocks length 12
    tests.push_back("FFWWEEFFWWEE"); // length 12

    // 8) Programmatically build length 20: repeating "FWE"
    string s7; s7.reserve(20);
    for (int i = 0; i < 20; ++i) s7.push_back("FWE"[i % 3]);
    tests.push_back(s7);

    // 9) Programmatically build length 30: repeating "FEW"
    string s8; s8.reserve(30);
    for (int i = 0; i < 30; ++i) s8.push_back("FEW"[i % 3]);
    tests.push_back(s8);

    // 10) Programmatically build length 40: pseudo-random over {'F','W','E'}
    string s9; s9.reserve(40);
    int seed = 7;
    const char map_chars[3] = {'F', 'W', 'E'};
    for (int i = 0; i < 40; ++i) {
        seed = (seed * 37 + 11) % 3;
        s9.push_back(map_chars[seed]);
    }
    tests.push_back(s9);

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += sol.countWinningSequences(s);
            checksum ^= (iter + s.size()); // perturb to avoid easy optimization
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}