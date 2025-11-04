#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

class Solution {
public:
    int racecar(int target) {
        // Time : O(nlogn), n is the value of the target
        // Space: O(n)
        std::vector<int> dp(target + 1, 0);
        for (int i = 1; i <= target; ++i) {
            // 2^(k-1) <= i < 2^k
            int k = 0;
            while ((1 << k) <= i) ++k;

            // case 1. drive exactly i at best
            //         seq(i) = A^k
            if (i == (1 << k) - 1) {
                dp[i] = k;
                continue;
            }

            // case 2. drive cross i at 2^k-1, and turn back to i
            //         seq(i) = A^k -> R -> seq(2^k-1 - i)
            dp[i] = k + 1 + dp[(1 << k) - 1 - i];

            // case 3. drive less then 2^k-1, and turn back some distance,
            //         and turn back again to make the direction is the same
            //         seq(i) = shortest(seq(i), A^(k-1) -> R -> A^j -> R ->
            //                                   seq(i - (2^(k-1)-1) + (2^j-1)),
            //                  where 0 <= j < k-1)
            //         => dp[i] = min(dp[i], (k-1) + 1 + j + 1 +
            //                               dp[i - (2**(k-1)-1) + (2**j-1)])
            for (int j = 0; j < k - 1; ++j) {
                dp[i] = std::min(dp[i], (k - 1) + 1 + j + 1 + dp[i - (1 << (k - 1)) + (1 << j)]);
            }
        }
        return dp[target];
    }
};

int main() {
    // 10 diverse test inputs for the racecar problem
    std::vector<int> tests = {
        1,   // minimal
        2,   // small
        3,   // 2^2 - 1
        4,   // power of two
        6,   // just below 7
        7,   // 2^3 - 1
        9,   // just above 8
        15,  // 2^4 - 1
        31,  // 2^5 - 1
        500  // larger target
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int t : tests) {
            checksum += sol.racecar(t);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = static_cast<double>(elapsed_ns) / 1e6;

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}