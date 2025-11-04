int main() {
    // 10 diverse test inputs for K
    vector<int> test_inputs = {
        0,          // expect 5
        1,          // expect 5
        4,          // expect 5
        5,          // expect 0
        6,          // expect 5
        10,         // expect 5
        24,         // expect 0
        25,         // expect 5
        100,        // commonly 0
        1000000000  // large K for stress
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // Slightly vary inputs each iteration to avoid code motion/hoisting
        for (size_t i = 0; i < test_inputs.size(); ++i) {
            int k = test_inputs[i] + (iter & 1); // toggle between k and k+1
            int result = sol.preimageSizeFZF(k);
            checksum += result;
            checksum ^= (static_cast<long long>(k) << (i % 23));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}