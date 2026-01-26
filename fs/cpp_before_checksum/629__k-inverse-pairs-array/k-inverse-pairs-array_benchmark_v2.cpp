#include <iostream>
#include <vector>
#include <utility>
using namespace std;

// Time:  O(n * k)
// Space: O(k)
// knapsack dp, combinatorics, sliding window, two pointers
class Solution {
public:
    int kInversePairs(int n, int k) {
        static const int MOD = 1000000007;
        if (k > n * (n - 1) / 2) return 0;
        if (k == 0) return 1;

        vector<int> dp(k + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n; ++i) {
            vector<int> new_dp(k + 1, 0);
            long long curr = 0;
            for (int j = 0; j <= k; ++j) {
                curr += dp[j];
                if (curr >= MOD) curr -= MOD;
                if (j - (i + 1) >= 0) {
                    curr -= dp[j - (i + 1)];
                    if (curr < 0) curr += MOD;
                }
                new_dp[j] = static_cast<int>(curr);
            }
            dp.swap(new_dp);
        }
        return dp[k];
    }
};

volatile int sink = 0;

int main() {
    Solution sol;

    vector<pair<int,int>> tests = {
        {1, 0},
        {2, 1},
        {3, 2},
        {4, 6},
        {5, 5},
        {10, 12},
        {15, 20},
        {20, 10},
        {30, 100},
        {50, 200}
    };

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.kInversePairs(t.first, t.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}