#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <utility>

class Solution {
public:
    int cherryPickup(std::vector<std::vector<int>>& grid) {
        int n = static_cast<int>(grid.size());
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, -1));
        dp[0][0] = grid[0][0];
        int max_len = 2 * (n - 1);
        const std::vector<std::pair<int, int>> directions = {{0, 0}, {-1, 0}, {0, -1}, {-1, -1}};
        for (int k = 1; k <= max_len; ++k) {
            int i_start = std::max(0, k - n + 1);
            int i_end = std::min(k, n - 1);
            for (int i = i_end; i >= i_start; --i) {  // 0 <= i < n, 0 <= k-i < n
                int j_start = i;
                int j_end = std::min(k, n - 1);
                for (int j = j_end; j >= j_start; --j) {  // i <= j < n, 0 <= k-j < n
                    if (grid[i][k - i] == -1 || grid[j][k - j] == -1) {
                        dp[i][j] = -1;
                        continue;
                    }
                    int cnt = grid[i][k - i];
                    if (i != j) {
                        cnt += grid[j][k - j];
                    }
                    int max_cnt = -1;
                    for (const auto& d : directions) {
                        int ii = i + d.first;
                        int jj = j + d.second;
                        if (ii >= 0 && jj >= 0 && dp[ii][jj] >= 0) {
                            max_cnt = std::max(max_cnt, dp[ii][jj] + cnt);
                        }
                    }
                    dp[i][j] = max_cnt;
                }
            }
        }
        return std::max(dp[n - 1][n - 1], 0);
    }
};

int main() {
    std::vector<std::vector<std::vector<int>>> tests = {
        // 1
        {{1}},
        // 2
        {{1,1},
         {1,1}},
        // 3
        {{0,1,-1},
         {1,0,-1},
         {1,1,1}},
        // 4 (no valid path)
        {{1,-1,1},
         {-1,-1,-1},
         {1,-1,1}},
        // 5
        {{1,1,1,1},
         {1,-1,1,1},
         {1,1,-1,1},
         {1,1,1,1}},
        // 6
        {{0,0,0,0,1},
         {0,-1,-1,0,0},
         {0,1,0,1,0},
         {0,0,-1,0,0},
         {1,0,0,0,0}},
        // 7
        {{1,1,1,1,1},
         {1,-1,1,-1,1},
         {1,1,1,1,1},
         {1,-1,1,-1,1},
         {1,1,1,1,1}},
        // 8
        {{0,1,0,1,0,1},
         {1,-1,1,-1,1,0},
         {0,1,0,1,0,1},
         {1,-1,1,-1,1,0},
         {0,1,0,1,0,1},
         {1,0,1,0,1,0}},
        // 9
        {{1,-1},
         {1,1}},
        // 10
        {{1,1,0,1,0,1,1},
         {0,-1,1,0,1,0,1},
         {1,0,1,1,0,1,0},
         {1,1,0,-1,1,1,1},
         {0,1,1,0,1,0,1},
         {1,0,1,1,0,1,0},
         {1,1,0,1,1,0,1}}
    };

    volatile int sink = 0;
    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& grid : tests) {
            int r = sol.cherryPickup(grid);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}