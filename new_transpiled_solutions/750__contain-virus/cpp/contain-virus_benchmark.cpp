#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <chrono>

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

int main() {
    // Define 10 diverse test inputs (grids)
    std::vector<std::vector<std::vector<int>>> tests;

    // 1) Single infection in center of 5x5
    {
        std::vector<std::vector<int>> g(5, std::vector<int>(5, 0));
        g[2][2] = 1;
        tests.push_back(g);
    }

    // 2) Four corners infected in 5x5
    {
        std::vector<std::vector<int>> g(5, std::vector<int>(5, 0));
        g[0][0] = g[0][4] = g[4][0] = g[4][4] = 1;
        tests.push_back(g);
    }

    // 3) 6x6 checkerboard starting with 1
    {
        std::vector<std::vector<int>> g(6, std::vector<int>(6, 0));
        for (int r = 0; r < 6; ++r) {
            for (int c = 0; c < 6; ++c) {
                g[r][c] = ((r + c) % 2 == 0) ? 1 : 0;
            }
        }
        tests.push_back(g);
    }

    // 4) 4x4 all zeros
    {
        std::vector<std::vector<int>> g(4, std::vector<int>(4, 0));
        tests.push_back(g);
    }

    // 5) 4x4 all ones
    {
        std::vector<std::vector<int>> g(4, std::vector<int>(4, 1));
        tests.push_back(g);
    }

    // 6) 15x15 deterministic pseudo-random pattern
    {
        std::vector<std::vector<int>> g(15, std::vector<int>(15, 0));
        for (int r = 0; r < 15; ++r) {
            for (int c = 0; c < 15; ++c) {
                g[r][c] = (((r * 31 + c * 17) % 7) == 0) ? 1 : 0;
            }
        }
        tests.push_back(g);
    }

    // 7) 3x10 with middle row infected line
    {
        std::vector<std::vector<int>> g(3, std::vector<int>(10, 0));
        for (int c = 0; c < 10; ++c) g[1][c] = 1;
        tests.push_back(g);
    }

    // 8) 10x3 with middle column infected line
    {
        std::vector<std::vector<int>> g(10, std::vector<int>(3, 0));
        for (int r = 0; r < 10; ++r) g[r][1] = 1;
        tests.push_back(g);
    }

    // 9) 7x7 with 3x3 block in center
    {
        std::vector<std::vector<int>> g(7, std::vector<int>(7, 0));
        for (int r = 2; r <= 4; ++r)
            for (int c = 2; c <= 4; ++c)
                g[r][c] = 1;
        tests.push_back(g);
    }

    // 10) 10x10 with two 3x3 blocks and some noise
    {
        std::vector<std::vector<int>> g(10, std::vector<int>(10, 0));
        for (int r = 1; r <= 3; ++r)
            for (int c = 1; c <= 3; ++c)
                g[r][c] = 1;
        for (int r = 6; r <= 8; ++r)
            for (int c = 6; c <= 8; ++c)
                g[r][c] = 1;
        g[0][9] = 1;
        g[9][0] = 1;
        g[4][5] = 1;
        tests.push_back(g);
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            std::vector<std::vector<int>> grid = tests[i]; // copy since function mutates
            int res = sol.containVirus(grid);
            checksum += res;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}