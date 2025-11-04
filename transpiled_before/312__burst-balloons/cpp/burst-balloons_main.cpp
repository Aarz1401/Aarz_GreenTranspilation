int main() {
    // Define 10 diverse test inputs
    std::vector<std::vector<int>> tests = {
        {},                                   // 1. Empty
        {5},                                  // 2. Single element
        {1, 5},                               // 3. Two elements
        {0, -1, 2, 0, 3, -5},                 // 4. Zeros and negatives
        {1,1,1,1,1,1,1,1},                    // 5. All ones
        {1,2,3,4,5},                          // 6. Increasing
        {5,4,3,2,1},                          // 7. Decreasing
        {7,9,8,0,1,2,3},                      // 8. Mixed with zero
        {100, 1, 100, 1, 100},                // 9. Larger values mix
        {3,1,5,8,2,7,9,4,6,1,2,3}             // 10. Longer mixed
    };

    Solution sol;
    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code here
        for (size_t t = 0; t < tests.size(); ++t) {
            std::vector<int> data = tests[t]; // copy per run
            int res = sol.maxCoins(data);
            checksum += static_cast<long long>(res) + static_cast<long long>((iter + 1) * (t + 1));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}