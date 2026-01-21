#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>

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
    vector<vector<vector<int>>> test_cases;
    test_cases.reserve(10);

    // 1) Empty matrix
    test_cases.push_back(vector<vector<int>>{});

    // 2) Matrix with one empty row
    test_cases.push_back(vector<vector<int>>{vector<int>{}});

    // 3) Single element
    test_cases.push_back(vector<vector<int>>{{42}});

    // 4) Increasing row
    test_cases.push_back(vector<vector<int>>{{1, 2, 3, 4, 5}});

    // 5) Increasing column
    test_cases.push_back(vector<vector<int>>{{1}, {2}, {3}, {4}, {5}});

    // 6) LeetCode example with plateaus
    test_cases.push_back(vector<vector<int>>{{9, 9, 4}, {6, 6, 8}, {2, 1, 1}});

    // 7) Strictly decreasing grid (long increasing path from low to high)
    test_cases.push_back(vector<vector<int>>{{9, 8, 7}, {6, 5, 4}, {3, 2, 1}});

    // 8) Constant grid
    test_cases.push_back(vector<vector<int>>{{7, 7, 7}, {7, 7, 7}, {7, 7, 7}});

    // 9) Zigzag/serpentine
    test_cases.push_back(vector<vector<int>>{
        {10,  9,  4,  5},
        {11,  8,  7,  6},
        {12, 13, 14, 15},
        { 1,  2,  3, 16}
    });

    // 10) Mixed/random-like 5x5
    test_cases.push_back(vector<vector<int>>{
        { 7,  2,  3,  4,  5},
        {36, 35, 34, 33,  6},
        {37, 42, 43, 32,  7},
        {38, 41, 44, 31,  8},
        {39, 40, 45, 30,  9}
    });

    Solution sol;
    volatile long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& matrix : test_cases) {
            int r = sol.longestIncreasingPath(matrix);
            checksum += r;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}