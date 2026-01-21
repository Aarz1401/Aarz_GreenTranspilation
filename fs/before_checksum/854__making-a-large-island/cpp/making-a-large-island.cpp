#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        if (n == 0) return 0;
        vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
        
        function<int(int, int, int)> dfs = [&](int r, int c, int index) -> int {
            if (!(r >= 0 && r < n && c >= 0 && c < n && grid[r][c] == 1)) {
                return 0;
            }
            int result = 1;
            grid[r][c] = index;
            for (const auto& d : directions) {
                result += dfs(r + d.first, c + d.second, index);
            }
            return result;
        };

        unordered_map<int, int> area;
        int idx = 2;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 1) {
                    area[idx] = dfs(r, c, idx);
                    ++idx;
                }
            }
        }

        int result = 0;
        for (const auto& kv : area) {
            result = max(result, kv.second);
        }

        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (grid[r][c] == 0) {
                    unordered_set<int> seen;
                    for (const auto& d : directions) {
                        int nr = r + d.first, nc = c + d.second;
                        if (!(nr >= 0 && nr < n && nc >= 0 && nc < n)) continue;
                        if (grid[nr][nc] > 1) {
                            seen.insert(grid[nr][nc]);
                        }
                    }
                    int sum = 1;
                    for (int id : seen) {
                        sum += area[id];
                    }
                    result = max(result, sum);
                }
            }
        }

        return result;
    }
};