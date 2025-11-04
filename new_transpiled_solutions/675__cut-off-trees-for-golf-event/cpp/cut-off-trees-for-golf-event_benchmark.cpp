#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <chrono>

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse test inputs
    vector<vector<int>> f1; // empty -> -1
    vector<vector<int>> f2 = { { } }; // n == 0 -> -1
    vector<vector<int>> f3 = { {0} }; // start blocked -> -1
    vector<vector<int>> f4 = { {1,1}, {1,1} }; // no trees -> 0
    vector<vector<int>> f5 = { {1,2} }; // single tree -> reachable
    vector<vector<int>> f6 = {
        {1,2,3},
        {0,0,4},
        {7,6,5}
    }; // reachable classic
    vector<vector<int>> f7 = {
        {1,2,3},
        {0,0,0},
        {4,5,6}
    }; // unreachable later -> -1
    vector<vector<int>> f8 = {
        {1,0,2,0,3},
        {0,4,0,5,0},
        {6,0,7,0,8},
        {0,9,0,10,0},
        {11,0,12,0,13}
    }; // unreachable early -> -1
    vector<vector<int>> f9 = {
        {1,1,1,1,1,1},
        {1,0,0,0,0,1},
        {1,1,2,3,0,1},
        {1,1,4,5,0,1},
        {1,1,6,7,0,1},
        {1,1,1,1,1,1}
    }; // reachable with corridor
    vector<vector<int>> f10 = {
        {1,2,3,4,5,6,7},
        {0,0,0,0,0,0,8},
        {15,14,13,12,11,10,9},
        {16,0,0,0,0,0,0},
        {17,18,19,20,21,22,23}
    }; // zigzag path reachable

    long long checksum = 0;

    const int iterations = 1000;
    auto begin = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        Solution sol;
        checksum += sol.cutOffTree(f1);
        checksum += sol.cutOffTree(f2);
        checksum += sol.cutOffTree(f3);
        checksum += sol.cutOffTree(f4);
        checksum += sol.cutOffTree(f5);
        checksum += sol.cutOffTree(f6);
        checksum += sol.cutOffTree(f7);
        checksum += sol.cutOffTree(f8);
        checksum += sol.cutOffTree(f9);
        checksum += sol.cutOffTree(f10);
        // minor dependency on iter to avoid over-aggressive optimization
        checksum += iter & 1;
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time: " << elapsed_us << " us\n";

    return 0;
}