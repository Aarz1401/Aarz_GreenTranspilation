int main() {
    // Define 10 diverse test inputs
    std::vector<std::vector<int>> tests;
    tests.push_back(make_identity(1));            // [0,1]
    tests.push_back(make_chain(2));               // N=2 chain
    tests.push_back(make_chain(3));               // N=3 chain
    tests.push_back(make_pair_reversed(4));       // within-pair reversed
    tests.push_back(make_alternating(5));         // evens then odds
    tests.push_back(make_random(8, 42));          // random with fixed seed
    tests.push_back(make_identity(12));           // larger identity
    tests.push_back(make_chain(25));              // medium chain
    tests.push_back(make_random(60, 1234567));    // larger random
    tests.push_back(make_chain(1000));            // big chain

    Solution solution;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& row : tests) {
            checksum += solution.minSwapsCouples(row);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}