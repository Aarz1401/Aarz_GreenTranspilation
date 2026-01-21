#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    int containVirus(std::vector<std::vector<int>>& grid) {
        m = grid.size();
        n = grid[0].size();
        int result = 0;

        while (true) {
            std::vector<std::vector<char>> visited(m, std::vector<char>(n, 0));
            std::vector<std::unordered_set<int>> regions;
            std::vector<std::unordered_set<int>> frontiers;
            std::vector<int> perimeters;

            for (int r = 0; r < m; ++r) {
                for (int c = 0; c < n; ++c) {
                    if (grid[r][c] == 1 && !visited[r][c]) {
                        regions.emplace_back();
                        frontiers.emplace_back();
                        perimeters.emplace_back(0);
                        dfs(grid, r, c, visited, regions, frontiers, perimeters, static_cast<int>(regions.size()) - 1);
                    }
                }
            }

            if (regions.empty()) break;

            int triage_idx = 0;
            size_t max_frontier = 0;
            for (int i = 0; i < static_cast<int>(frontiers.size()); ++i) {
                if (frontiers[i].size() > max_frontier) {
                    max_frontier = frontiers[i].size();
                    triage_idx = i;
                }
            }

            for (int i = 0; i < static_cast<int>(regions.size()); ++i) {
                if (i == triage_idx) {
                    result += perimeters[i];
                    for (int id : regions[i]) {
                        int r = id / n;
                        int c = id % n;
                        grid[r][c] = -1;  // quarantine
                    }
                } else {
                    for (int id : regions[i]) {
                        int r = id / n;
                        int c = id % n;
                        static const int dr[4] = {0, 0, -1, 1};
                        static const int dc[4] = {1, -1, 0, 0};
                        for (int d = 0; d < 4; ++d) {
                            int nr = r + dr[d], nc = c + dc[d];
                            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
                            if (grid[nr][nc] == 0) {
                                grid[nr][nc] = 1;
                            }
                        }
                    }
                }
            }
        }

        return result;
    }

private:
    int m = 0, n = 0;

    void dfs(const std::vector<std::vector<int>>& grid, int r, int c,
             std::vector<std::vector<char>>& visited,
             std::vector<std::unordered_set<int>>& regions,
             std::vector<std::unordered_set<int>>& frontiers,
             std::vector<int>& perimeters, int idx) {
        visited[r][c] = 1;
        regions[idx].insert(r * n + c);
        static const int dr[4] = {0, 0, -1, 1};
        static const int dc[4] = {1, -1, 0, 0};
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;
            if (grid[nr][nc] == 1) {
                if (!visited[nr][nc]) {
                    dfs(grid, nr, nc, visited, regions, frontiers, perimeters, idx);
                }
            } else if (grid[nr][nc] == 0) {
                frontiers[idx].insert(nr * n + nc);
                perimeters[idx] += 1;
            }
        }
    }
};

volatile int sink = 0;

int main() {
    std::vector<std::vector<std::vector<int>>> tests = {
        // 1) 1x1 healthy
        {{0}},
        // 2) 1x1 infected
        {{1}},
        // 3) 2x2 single infection
        {
            {1,0},
            {0,0}
        },
        // 4) 3x3 all infected
        {
            {1,1,1},
            {1,1,1},
            {1,1,1}
        },
        // 5) 3x4 scattered infections
        {
            {1,0,0,1},
            {0,0,0,0},
            {1,0,1,0}
        },
        // 6) 5x5 ring with center infection
        {
            {1,1,1,1,1},
            {1,0,0,0,1},
            {1,0,1,0,1},
            {1,0,0,0,1},
            {1,1,1,1,1}
        },
        // 7) 5x5 mixed pattern
        {
            {0,1,0,0,1},
            {1,1,0,1,0},
            {0,0,1,0,0},
            {1,0,0,1,1},
            {0,1,0,0,0}
        },
        // 8) 4x7 varied layout
        {
            {0,0,1,0,0,1,0},
            {1,0,1,0,0,0,0},
            {0,0,0,1,1,0,1},
            {1,1,0,0,0,0,0}
        },
        // 9) 8x8 moderate density
        {
            {0,1,0,0,1,0,0,1},
            {1,0,1,0,0,1,0,0},
            {0,0,0,1,0,0,1,0},
            {1,0,0,0,1,0,0,1},
            {0,1,0,0,0,1,0,0},
            {0,0,1,0,0,0,1,0},
            {1,0,0,1,0,0,0,1},
            {0,0,1,0,1,0,0,0}
        },
        // 10) 6x6 checkerboard starting with infected
        {
            {1,0,1,0,1,0},
            {0,1,0,1,0,1},
            {1,0,1,0,1,0},
            {0,1,0,1,0,1},
            {1,0,1,0,1,0},
            {0,1,0,1,0,1}
        }
    };

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            std::vector<std::vector<int>> grid = t;
            Solution s;
            int res = s.containVirus(grid);
            checksum += res;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}