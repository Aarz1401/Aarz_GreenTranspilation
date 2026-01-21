#include <iostream>
#include <vector>
#include <algorithm>

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