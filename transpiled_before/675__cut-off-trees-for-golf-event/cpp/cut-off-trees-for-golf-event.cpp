#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <utility>
#include <cstdlib>

using namespace std;

// Time:  O(t * (logt + m * n)), t is the number of trees
// Space: O(t + m * n)
class Solution {
public:
    int cutOffTree(vector<vector<int>>& forest) {
        int m = forest.size();
        if (m == 0) return -1;
        int n = forest[0].size();
        if (n == 0) return -1;
        if (forest[0][0] == 0) return -1;

        auto dot = [](int x1, int y1, int x2, int y2) -> int {
            return x1 * x2 + y1 * y2;
        };

        auto minStep = [&](pair<int, int> p1, pair<int, int> p2) -> int {
            int min_steps = std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
            vector<pair<int, int>> closer;
            vector<pair<int, int>> detour;
            closer.push_back(p1);
            vector<vector<bool>> visited(m, vector<bool>(n, false));

            while (true) {
                if (closer.empty()) {
                    if (detour.empty()) {
                        return -1;
                    }
                    min_steps += 2;
                    std::swap(closer, detour);
                }
                auto cur = closer.back();
                closer.pop_back();
                int i = cur.first, j = cur.second;
                if (i == p2.first && j == p2.second) {
                    return min_steps;
                }
                if (!visited[i][j]) {
                    visited[i][j] = true;
                    const int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
                    for (const auto& d : dirs) {
                        int I = i + d[0], J = j + d[1];
                        if (0 <= I && I < m && 0 <= J && J < n && forest[I][J] > 0 && !visited[I][J]) {
                            int move_x = I - i, move_y = J - j;
                            int to_target_x = p2.first - i, to_target_y = p2.second - j;
                            bool is_closer = dot(move_x, move_y, to_target_x, to_target_y) > 0;
                            if (is_closer) {
                                closer.emplace_back(I, J);
                            } else {
                                detour.emplace_back(I, J);
                            }
                        }
                    }
                }
            }
            // Unreachable
            // return min_steps;
        };

        vector<tuple<int, int, int>> trees;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (forest[i][j] > 1) {
                    trees.emplace_back(forest[i][j], i, j);
                }
            }
        }
        sort(trees.begin(), trees.end());

        pair<int, int> start = {0, 0};
        int result = 0;
        for (const auto& t : trees) {
            int ti = std::get<1>(t);
            int tj = std::get<2>(t);
            int step = minStep(start, {ti, tj});
            if (step < 0) {
                return -1;
            }
            result += step;
            start = {ti, tj};
        }
        return result;
    }
};