#include <iostream>
#include <vector>
#include <utility>
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

int main() {
    vector<vector<vector<int>>> tests = {
        {{42}},
        {{7, 7, 7}, {7, 7, 7}},
        {{1, 2, 3, 4, 5}},
        {{1}, {2}, {3}, {4}, {5}},
        {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}},
        {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}},
        {{1, 2, 3, 4}, {12, 13, 14, 5}, {11, 16, 15, 6}, {10, 9, 8, 7}},
        {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}},
        {{-1, -2, -3}, {-2, -3, -4}, {-3, -4, -5}},
        {{1, 2, 1, 2}, {2, 1, 2, 1}, {1, 2, 1, 2}, {2, 1, 2, 1}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t t = 0; t < tests.size(); ++t) {
            checksum += sol.longestIncreasingPath(tests[t]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}