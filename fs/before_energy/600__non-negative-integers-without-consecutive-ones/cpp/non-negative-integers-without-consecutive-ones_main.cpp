int main() {
    // Define 10 diverse test inputs for the function findIntegers(int)
    std::vector<int> inputs = {
        0,                  // smallest edge
        1,                  // simple base
        2,                  // small no consecutive ones
        3,                  // has consecutive ones (11)
        4,                  // power of two
        5,                  // alternating bits (101)
        6,                  // consecutive ones in middle (110)
        8,                  // another power of two
        21,                 // 10101 pattern
        1073741824          // 1 << 30 (top bit in loop range)
    };

    Solution sol;
    volatile unsigned long long checksum = 0; // prevent optimization

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int x : inputs) {
            checksum += sol.findIntegers(x);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}