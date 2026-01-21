int main() {
    // Define 10 diverse test inputs (within the expected range 1..8 for performance)
    vector<int> test_inputs = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    Solution sol;
    volatile long long checksum = 0; // volatile to help prevent aggressive optimization

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : test_inputs) {
            checksum += sol.largestPalindrome(n);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (nanoseconds): " << elapsed_ns << "\n";
    return 0;
}