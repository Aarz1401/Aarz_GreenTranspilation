int main() {
    vector<TestCase> tests = makeTestCases();

    Solution solver;
    volatile long long checksum = 0; // prevent optimization

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            Master master(tc.secret);
            // Make a modifiable copy since API expects non-const reference
            vector<string> words = tc.words;
            solver.findSecretWord(words, master);
            checksum += master.attempts();
        }
    }

    auto end = clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}