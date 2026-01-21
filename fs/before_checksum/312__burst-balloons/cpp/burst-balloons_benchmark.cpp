#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

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
    // Define 10 diverse test inputs
    std::vector<std::vector<int>> tests = {
        {},                                   // 1. Empty
        {5},                                  // 2. Single element
        {1, 5},                               // 3. Two elements
        {0, -1, 2, 0, 3, -5},                 // 4. Zeros and negatives
        {1,1,1,1,1,1,1,1},                    // 5. All ones
        {1,2,3,4,5},                          // 6. Increasing
        {5,4,3,2,1},                          // 7. Decreasing
        {7,9,8,0,1,2,3},                      // 8. Mixed with zero
        {100, 1, 100, 1, 100},                // 9. Larger values mix
        {3,1,5,8,2,7,9,4,6,1,2,3}             // 10. Longer mixed
    };

    Solution sol;
    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code here
        for (size_t t = 0; t < tests.size(); ++t) {
            std::vector<int> data = tests[t]; // copy per run
            int res = sol.maxCoins(data);
            checksum += static_cast<long long>(res) + static_cast<long long>((iter + 1) * (t + 1));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}