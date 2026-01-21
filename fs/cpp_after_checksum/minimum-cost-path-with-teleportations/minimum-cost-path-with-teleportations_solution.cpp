#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        const long long INF = (long long)4e18;

        vector<vector<long long>> dp(m, vector<long long>(n, INF));
        dp[m - 1][n - 1] = 0;

        int mx = 0;
        for (const auto& row : grid) {
            for (int v : row) {
                mx = max(mx, v);
            }
        }
        vector<long long> prefix(mx + 1, INF);

        for (int iter = 0; iter <= k; ++iter) {
            for (int r = m - 1; r >= 0; --r) {
                for (int c = n - 1; c >= 0; --c) {
                    if (r + 1 < m && dp[r + 1][c] != INF) {
                        dp[r][c] = min(dp[r][c], dp[r + 1][c] + (long long)grid[r + 1][c]);
                    }
                    if (c + 1 < n && dp[r][c + 1] != INF) {
                        dp[r][c] = min(dp[r][c], dp[r][c + 1] + (long long)grid[r][c + 1]);
                    }
                    long long tele = prefix[grid[r][c]];
                    if (tele < dp[r][c]) {
                        dp[r][c] = tele;
                    }
                }
            }
            for (int r = 0; r < m; ++r) {
                for (int c = 0; c < n; ++c) {
                    int val = grid[r][c];
                    if (dp[r][c] < prefix[val]) {
                        prefix[val] = dp[r][c];
                    }
                }
            }
            for (int i = 0; i < mx; ++i) {
                if (prefix[i] < prefix[i + 1]) {
                    prefix[i + 1] = prefix[i];
                }
            }
        }
        return (int)dp[0][0];
    }
};
