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
    // Define 10 diverse test inputs
    vector<vector<vector<int>>> tests;

    // 1) Single element
    tests.push_back({{0}});

    // 2) Single row
    tests.push_back({{1, 2, 3}});

    // 3) Single column
    tests.push_back({{1}, {2}, {4}});

    // 4) Uniform small matrix (balanced)
    tests.push_back({{1, 1}, {1, 1}});

    // 5) Mixed negatives, positives, and zeros
    tests.push_back({{-1, 2, 0}, {3, -2, 1}, {0, 0, 0}});

    // 6) 4x3 mixed values
    tests.push_back({{5, 7, 2}, {4, 9, 1}, {6, 3, 8}, {0, -2, 4}});

    // 7) Large numbers to test 64-bit accumulation
    tests.push_back({
        {1000000000, 1000000000, 1000000000, 999999999, 999999999},
        {1000000000, 999999999, 1000000000, 1000000000, 999999999}
    });

    // 8) 4x4 chessboard pattern
    tests.push_back({
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1}
    });

    // 9) 3x4 prime numbers
    tests.push_back({
        {2, 3, 5, 7},
        {11, 13, 17, 19},
        {23, 29, 31, 37}
    });

    // 10) 2x3 symmetric rows
    tests.push_back({
        {1, 2, 3},
        {3, 2, 1}
    });

    Solution sol;

    using clock = chrono::high_resolution_clock;
    auto start = clock::now();

    volatile int magic = 0; // prevent hoisting/constant folding of calls
    long long checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        magic ^= (iter & 1);
        for (size_t t = 0; t < tests.size(); ++t) {
            // Use volatile-dependent index to inhibit aggressive optimization
            size_t idx = (t + magic) % tests.size();
            bool result = sol.canPartitionGrid(tests[idx]);
            checksum += result ? 1 : 0;
        }
    }

    auto end = clock::now();
    auto elapsed = chrono::duration_cast<chrono::duration<double, std::milli>>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Time (ms): " << elapsed << "\n";

    return 0;
}