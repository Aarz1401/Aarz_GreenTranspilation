#include <vector>
#include <unordered_set>
#include <functional>

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
    vector<vector<vector<int>>> tests = {
        {{0}},
        {{5}},
        {{1, 2}},
        {{1}, {2}},
        {{1, 2}, {3, 4}},
        {{1, 1, 1}, {1, 1, 1}},
        {{3, 1, 2}, {4, 0, 5}, {6, 7, 8}},
        {{10, 20, 30, 40}},
        {{2, 2, 2}, {2, 2, 2}, {2, 2, 2}, {2, 2, 2}},
        {{9, 8, 7, 6}, {5, 4, 3, 2}, {1, 0, 1, 0}}
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& grid : tests) {
            checksum += s.canPartitionGrid(grid);
        }
        sink = checksum;
    }

    return 0;
}