#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxCoins(std::vector<int>& nums) {
        std::vector<int> coins;
        coins.reserve(nums.size() + 2);
        coins.push_back(1);
        for (int x : nums) {
            if (x > 0) coins.push_back(x);
        }
        coins.push_back(1);

        int n = static_cast<int>(coins.size());
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        for (int k = 2; k < n; ++k) {
            for (int left = 0; left + k < n; ++left) {
                int right = left + k;
                for (int i = left + 1; i < right; ++i) {
                    dp[left][right] = std::max(
                        dp[left][right],
                        coins[left] * coins[i] * coins[right] + dp[left][i] + dp[i][right]
                    );
                }
            }
        }

        return dp[0][n - 1];
    }
};