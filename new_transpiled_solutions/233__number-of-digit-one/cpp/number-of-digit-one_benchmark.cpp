#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cstdint>
#include <chrono>

class Solution {
public:
    int countDigitOne(int n) {
        const long long DIGIT = 1;
        int is_zero = (DIGIT == 0) ? 1 : 0;
        long long result = is_zero;
        long long base = 1;
        while (static_cast<long long>(n) >= base) {
            long long tenbase = base * 10;
            result += (static_cast<long long>(n) / tenbase - is_zero) * base +
                      std::min(base, std::max(static_cast<long long>(n) % tenbase - DIGIT * base + 1, 0LL));
            base *= 10;
        }
        return static_cast<int>(result);
    }
};

int main() {
    // 10 diverse test inputs for the countDigitOne function
    std::vector<int> testInputs = {
        0,              // edge case: zero
        1,              // minimal positive
        9,              // single digit max
        10,             // transition to two digits
        11,             // multiple ones
        19,             // teen boundary
        20,             // no ones in tens place
        99,             // just before 100
        1000000,        // large power-of-10 boundary
        2000000000      // very large within int range
    };

    Solution solver;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : testInputs) {
            checksum += solver.countDigitOne(n);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}