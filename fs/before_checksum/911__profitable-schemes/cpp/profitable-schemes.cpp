#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>

using namespace std;

// Time:  O(n * p * g)
// Space: O(p * g)

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        const int MOD = 1000000007;
        int G = n, P = minProfit;
        vector<vector<int>> dp(P + 1, vector<int>(G + 1, 0));
        dp[0][0] = 1;
        for (size_t idx = 0; idx < group.size(); ++idx) {
            int g = group[idx];
            int p = profit[idx];
            for (int i = P; i >= 0; --i) {
                int ni = min(P, i + p);
                for (int j = G - g; j >= 0; --j) {
                    if (dp[i][j]) {
                        int nj = j + g;
                        dp[ni][nj] += dp[i][j];
                        if (dp[ni][nj] >= MOD) dp[ni][nj] -= MOD;
                    }
                }
            }
        }
        int ans = 0;
        for (int j = 0; j <= G; ++j) {
            ans += dp[P][j];
            if (ans >= MOD) ans -= MOD;
        }
        return ans;
    }
};