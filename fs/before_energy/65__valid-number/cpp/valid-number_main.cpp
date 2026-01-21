int main() {
    // Define 10 diverse test inputs
    std::vector<std::string> tests = {
        "0",
        " 0.1 ",
        "abc",
        "1 a",
        "2e10",
        " -90e3   ",
        " 1e",
        "e3",
        " 6e-1",
        " 99e2.5 "
    };

    Solution sol;
    volatile std::size_t checksum = 0; // volatile to prevent optimization

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (std::size_t i = 0; i < tests.size(); ++i) {
            bool res = sol.isNumber(tests[i]);
            // Mix iteration index, test index, and string size to form a checksum
            checksum += res ? (static_cast<std::size_t>(iter) + i + tests[i].size())
                            : ((static_cast<std::size_t>(iter) ^ i) + tests[i].size());
        }
    }

    auto end = clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}