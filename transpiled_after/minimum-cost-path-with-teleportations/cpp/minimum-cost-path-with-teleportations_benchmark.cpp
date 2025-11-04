#include <iostream>
#include <vector>
#include <algorithm>
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<vector<int>>> grids;
    vector<int> ks;

    // 1) 1x1 grid
    grids.push_back({{0}});
    ks.push_back(0);

    // 2) 1x5 increasing
    grids.push_back({{1, 2, 3, 4, 5}});
    ks.push_back(0);

    // 3) 5x1 decreasing
    grids.push_back({{5}, {4}, {3}, {2}, {1}});
    ks.push_back(0);

    // 4) 3x3 with barriers and many small values to exercise teleport
    grids.push_back({{1, 100, 1},
                     {1, 100, 1},
                     {1,   1, 1}});
    ks.push_back(1);

    // 5) 4x4 with zeros and blocks
    grids.push_back({{0, 0, 0, 0},
                     {0, 5, 5, 0},
                     {0, 5, 5, 0},
                     {0, 0, 0, 0}});
    ks.push_back(2);

    // 6) 2x3 mixed small values
    grids.push_back({{7, 2, 9},
                     {1, 3, 4}});
    ks.push_back(1);

    // 7) 3x2 mixed small values
    grids.push_back({{8, 1},
                     {6, 2},
                     {4, 3}});
    ks.push_back(2);

    // 8) 5x5 pattern with many duplicates to encourage teleport
    grids.push_back({{9, 8, 7, 6, 5},
                     {1, 1, 1, 1, 1},
                     {5, 6, 7, 8, 9},
                     {2, 2, 2, 2, 2},
                     {9, 9, 9, 9, 9}});
    ks.push_back(3);

    // 9) 2x4 varied values
    grids.push_back({{3, 1, 4, 1},
                     {5, 9, 2, 6}});
    ks.push_back(1);

    // 10) 1x10 alternating zeros and ones
    grids.push_back({{0, 1, 0, 1, 0, 1, 0, 1, 0, 1}});
    ks.push_back(4);

    Solution solution;
    long long aggregate = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t idx = 0; idx < grids.size(); ++idx) {
            aggregate += solution.minCost(grids[idx], ks[idx]);
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::milliseconds>(end - start).count();

    cout << "Aggregate result: " << aggregate << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}