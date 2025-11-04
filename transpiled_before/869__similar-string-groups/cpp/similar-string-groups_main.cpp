int main() {
    vector<vector<string>> tests = buildTests();
    Solution sol;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    long long checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& test : tests) {
            vector<string> input = test; // copy to avoid any accidental aliasing
            int result = sol.numSimilarGroups(input);
            checksum += result;
        }
    }

    auto end = clock::now();
    chrono::duration<double, milli> ms = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << ms.count() << "\n";

    return 0;
}