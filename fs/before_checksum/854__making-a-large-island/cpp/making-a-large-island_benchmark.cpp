#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <functional>
#include <utility>
#include <chrono>

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

int main() {
    // Prepare 10 diverse test grids
    vector<vector<vector<int>>> tests;

    // 1) Empty grid
    tests.push_back({});

    // 2) 1x1 zero
    tests.push_back({{0}});

    // 3) 1x1 one
    tests.push_back({{1}});

    // 4) 3x3 all zeros
    tests.push_back({
        {0,0,0},
        {0,0,0},
        {0,0,0}
    });

    // 5) 3x3 all ones
    tests.push_back({
        {1,1,1},
        {1,1,1},
        {1,1,1}
    });

    // 6) 4x4 checkerboard
    tests.push_back({
        {0,1,0,1},
        {1,0,1,0},
        {0,1,0,1},
        {1,0,1,0}
    });

    // 7) 3x3 center zero (connects all when flipped)
    tests.push_back({
        {1,1,1},
        {1,0,1},
        {1,1,1}
    });

    // 8) 5x5 island with holes (donut shape)
    tests.push_back({
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,1,0,1},
        {1,0,0,0,1},
        {1,1,1,1,1}
    });

    // 9) 30x30 patterned grid
    {
        vector<vector<int>> big(30, vector<int>(30, 0));
        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 30; ++j) {
                big[i][j] = ((i * j + i + j) % 3 == 0) ? 1 : 0;
            }
        }
        tests.push_back(big);
    }

    // 10) 2x5 irregular pattern
    tests.push_back({
        {1,1,0,1,0},
        {0,1,1,0,1}
    });

    Solution sol;
    long long checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            auto grid = tests[t]; // copy since algorithm mutates the grid
            int res = sol.largestIsland(grid);
            checksum += res + static_cast<int>(t) + iter;
        }
    }

    auto end = clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}