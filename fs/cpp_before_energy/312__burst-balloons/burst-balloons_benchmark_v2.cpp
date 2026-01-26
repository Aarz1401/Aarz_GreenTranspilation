#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    std::vector<std::vector<int>> tests = {
        {3, 1, 5, 8},
        {1},
        {9, 76, 64, 21},
        {1, 5},
        {7, 0, 2, 0, 9},
        {8, 2, 6, 8, 1, 4},
        {2, 2, 2, 2, 2, 2, 2, 2},
        {100, 1, 100, 1, 100},
        {2, 4, 3, 5, 1, 2},
        {1, 0, 3, 0, 5, 0, 8, 0, 13, 0, 21}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        Solution sol;
        for (auto& t : tests) {
            int r = sol.maxCoins(t);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}