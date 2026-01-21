#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <chrono>

class Solution {
public:
    int checkRecord(int n) {
        const int MOD = 1000000007;
        long long a0l0 = 1, a0l1 = 0, a0l2 = 0;
        long long a1l0 = 0, a1l1 = 0, a1l2 = 0;
        for (int i = 0; i <= n; ++i) {
            long long na0l2 = a0l1;
            long long na0l1 = a0l0;
            long long na0l0 = (a0l0 + a0l1 + a0l2) % MOD;

            long long na1l2 = a1l1;
            long long na1l1 = a1l0;
            long long na1l0 = (na0l0 + a1l0 + a1l1 + a1l2) % MOD;

            a0l2 = na0l2; a0l1 = na0l1; a0l0 = na0l0;
            a1l2 = na1l2; a1l1 = na1l1; a1l0 = na1l0;
        }
        return static_cast<int>(a1l0);
    }
};

int main() {
    // Define 10 diverse test inputs for the solution
    const std::array<int, 10> inputs = {0, 1, 2, 3, 4, 5, 10, 50, 100, 5000};

    Solution sol;
    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : inputs) {
            checksum += sol.checkRecord(n);
        }
    }

    auto end = clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}