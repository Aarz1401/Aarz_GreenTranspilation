#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <functional>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        long long total = 0;
        for (const auto& row : grid) {
            for (int v : row) {
                total += v;
            }
        }

        vector<int> rowsAsc(m), rowsDesc(m), colsAsc(n), colsDesc(n);
        for (int i = 0; i < m; ++i) {
            rowsAsc[i] = i;
            rowsDesc[i] = m - 1 - i;
        }
        for (int j = 0; j < n; ++j) {
            colsAsc[j] = j;
            colsDesc[j] = n - 1 - j;
        }

        auto check = [&](const vector<int>& range1, const vector<int>& range2, const function<long long(int, int)>& get) -> bool {
            long long curr = 0;
            unordered_set<long long> lookup;
            int begin = -1;
            bool hasBegin = false;
            int j_last = 0;

            for (int i : range1) {
                if (!hasBegin) {
                    begin = i;
                    hasBegin = true;
                }
                for (int j : range2) {
                    curr += get(i, j);
                    lookup.insert(get(i, j));
                    j_last = j;
                }
                long long diff = curr - (total - curr);
                if (diff == 0) {
                    return true;
                }
                if (i != begin && j_last != 0) {
                    if (lookup.count(diff)) {
                        return true;
                    }
                } else if (i == begin) {
                    if (diff == get(begin, 0) || diff == get(begin, j_last)) {
                        return true;
                    }
                } else {
                    if (diff == get(begin, 0) || diff == get(i, 0)) {
                        return true;
                    }
                }
            }
            return false;
        };

        if (check(rowsAsc, colsAsc, [&](int i, int j) -> long long { return (long long)grid[i][j]; })) return true;
        if (check(rowsDesc, colsAsc, [&](int i, int j) -> long long { return (long long)grid[i][j]; })) return true;
        if (check(colsAsc, rowsAsc, [&](int i, int j) -> long long { return (long long)grid[j][i]; })) return true;
        if (check(colsDesc, rowsAsc, [&](int i, int j) -> long long { return (long long)grid[j][i]; })) return true;

        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs (grids)
    vector<vector<vector<int>>> tests;

    // 1) 1x1 grid
    tests.push_back({{5}});

    // 2) 1x5 grid
    tests.push_back({{1, 2, 3, 4, 5}});

    // 3) 5x1 grid
    tests.push_back({{1}, {2}, {3}, {4}, {5}});

    // 4) 2x3 grid
    tests.push_back({{3, 1, 2},
                     {4, 6, 5}});

    // 5) 3x3 all zeros
    tests.push_back({{0, 0, 0},
                     {0, 0, 0},
                     {0, 0, 0}});

    // 6) 4x4 mixed positive values
    tests.push_back({{10, 20, 30, 40},
                     {5, 15, 25, 35},
                     {7, 14, 21, 28},
                     {1, 2, 3, 4}});

    // 7) 3x4 with negatives and positives
    tests.push_back({{-1, 2, -3, 4},
                     {5, -6, 7, -8},
                     {9, -10, 11, -12}});

    // 8) 6x6 sequential values
    {
        vector<vector<int>> g(6, vector<int>(6));
        int val = 1;
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                g[i][j] = val++;
            }
        }
        tests.push_back(std::move(g));
    }

    // 9) 8x3 patterned values
    {
        vector<vector<int>> g(8, vector<int>(3));
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 3; ++j) {
                g[i][j] = (i + 1) * (j + 2) - (i % 3) + (j % 2);
            }
        }
        tests.push_back(std::move(g));
    }

    // 10) 10x10 with modular pattern including negatives
    {
        vector<vector<int>> g(10, vector<int>(10));
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                g[i][j] = ((i * i + j * j + i * j) % 100) - 50;
            }
        }
        tests.push_back(std::move(g));
    }

    Solution sol;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    long long checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            checksum += sol.canPartitionGrid(tests[t]);
        }
    }

    auto end = Clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}