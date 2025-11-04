#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// Time:  O(m * n)
// Space: O(m * n)

// topological sort solution
class Solution {
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // directions: left, right, up, down
        const vector<pair<int, int>> directions = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int m = matrix.size();
        int n = matrix[0].size();

        vector<vector<int>> in_degree(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (const auto& dir : directions) {
                    int ni = i + dir.first, nj = j + dir.second;
                    if (0 <= ni && ni < m && 0 <= nj && nj < n &&
                        matrix[ni][nj] > matrix[i][j]) {
                        in_degree[i][j] += 1;
                    }
                }
            }
        }

        vector<pair<int, int>> q;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (in_degree[i][j] == 0) {
                    q.emplace_back(i, j);
                }
            }
        }

        int result = 0;
        while (!q.empty()) {
            vector<pair<int, int>> new_q;
            for (const auto& cell : q) {
                int i = cell.first, j = cell.second;
                for (const auto& dir : directions) {
                    int ni = i + dir.first, nj = j + dir.second;
                    if (0 <= ni && ni < m && 0 <= nj && nj < n &&
                        matrix[i][j] > matrix[ni][nj]) {
                        in_degree[ni][nj] -= 1;
                        if (in_degree[ni][nj] == 0) {
                            new_q.emplace_back(ni, nj);
                        }
                    }
                }
            }
            q.swap(new_q);
            result += 1;
        }
        return result;
    }
};