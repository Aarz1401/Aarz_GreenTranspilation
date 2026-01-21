#include <iostream>
#include <vector>
#include <chrono>

class Solution {
public:
    int findIntegers(int num) {
        std::vector<int> dp(32, 0);
        dp[0] = 1;
        dp[1] = 2;
        for (int i = 2; i < 32; ++i) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        int result = 0;
        int prev_bit = 0;
        for (int i = 30; i >= 0; --i) {
            if (num & (1 << i)) {
                result += dp[i];
                if (prev_bit == 1) {
                    result -= 1;
                    break;
                }
                prev_bit = 1;
            } else {
                prev_bit = 0;
            }
        }
        return result + 1;
    }
};

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

    const int iterations = 1;
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