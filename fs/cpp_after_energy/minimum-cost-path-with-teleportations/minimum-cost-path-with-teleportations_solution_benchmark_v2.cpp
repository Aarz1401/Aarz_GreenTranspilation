#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    vector<pair<vector<vector<int>>, int>> tests = {
        { { {0} }, 0 },
        { { {1, 2}, {3, 4} }, 0 },
        { { {1, 100, 1}, {1, 100, 1}, {1, 1, 1} }, 1 },
        { { {5, 1, 3, 2}, {4, 2, 1, 9}, {8, 1, 1, 1} }, 2 },
        { { {7, 7, 7}, {7, 5, 7}, {7, 7, 7}, {1, 1, 1} }, 3 },
        { { {1, 2, 3, 4, 5}, {2, 3, 4, 5, 6}, {3, 4, 5, 6, 7}, {4, 5, 6, 7, 1}, {5, 6, 7, 1, 2} }, 5 },
        { { {9, 8, 7, 6, 5}, {1, 2, 3, 4, 5} }, 10 },
        { { {0, 2, 1, 0, 3, 1}, {4, 0, 2, 1, 0, 2}, {1, 3, 0, 2, 2, 0}, {2, 1, 2, 0, 1, 3}, {0, 2, 1, 3, 0, 1}, {1, 0, 2, 1, 2, 0} }, 0 },
        { { {3, 1, 4, 1, 5} }, 2 },
        { { {2}, {7}, {1}, {8}, {2} }, 2 }
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& tc : tests) {
            int r = sol.minCost(tc.first, tc.second);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}