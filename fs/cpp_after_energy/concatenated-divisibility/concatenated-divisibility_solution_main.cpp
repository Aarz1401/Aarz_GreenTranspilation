int main() {
    vector<TestCase> tests;
    tests.push_back({{1, 2}, 3});                           // simple small case
    tests.push_back({{-1, 2, -3}, 7});                      // includes negatives
    tests.push_back({{0, 0, 5}, 5});                        // zeros with divisibility
    tests.push_back({{12, 34, 56}, 11});                    // multi-digit numbers
    tests.push_back({{123, 4, 56, 7}, 13});                 // mixed lengths
    tests.push_back({{10, 10, 10}, 10});                    // duplicates
    tests.push_back({{0}, 1});                              // single zero, k=1
    tests.push_back({{-999}, 3});                           // single negative divisible
    tests.push_back({{8, 80, 800, 5, 50, 500, 7, 70}, 9});  // larger set
    tests.push_back({{-12, 3, -45, 6, 789}, 37});           // mixed signs and sizes

    Solution solver;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            auto res = solver.concatenatedDivisibility(tests[t].nums, tests[t].k);
            uint64_t local = 0;
            for (int v : res) {
                local = local * 1315423911ull + static_cast<uint64_t>(v + 1000003);
            }
            checksum ^= (local + static_cast<uint64_t>(tests[t].k) * 2654435761ull + static_cast<uint64_t>(t));
            checksum += res.size();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}