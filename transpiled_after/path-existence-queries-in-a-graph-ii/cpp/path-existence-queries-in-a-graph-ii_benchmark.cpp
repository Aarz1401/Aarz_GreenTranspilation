#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>

using namespace std;

class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> sorted_i(n);
        iota(sorted_i.begin(), sorted_i.end(), 0);
        sort(sorted_i.begin(), sorted_i.end(), [&](int a, int b) {
            return nums[a] < nums[b];
        });

        vector<int> i_to_idx(n);
        for (int idx = 0; idx < n; ++idx) {
            i_to_idx[sorted_i[idx]] = idx;
        }

        vector<int> prefix(n, 0);
        for (int i = 0; i + 1 < n; ++i) {
            long long diff = (long long)nums[sorted_i[i + 1]] - (long long)nums[sorted_i[i]];
            prefix[i + 1] = prefix[i] + (diff > (long long)maxDiff ? 1 : 0);
        }

        int max_log = 0;
        while ((1 << max_log) <= n) {
            ++max_log;
        }
        vector<vector<int>> P(max_log, vector<int>(n, n - 1));

        int left = 0;
        for (int right = 0; right < n; ++right) {
            while ((long long)nums[sorted_i[right]] - (long long)nums[sorted_i[left]] > (long long)maxDiff) {
                P[0][left] = right - 1;
                ++left;
            }
        }

        for (int i = 0; i + 1 < max_log; ++i) {
            for (int j = 0; j < n; ++j) {
                P[i + 1][j] = P[i][P[i][j]];
            }
        }

        vector<int> result(queries.size(), -1);
        for (int idx = 0; idx < (int)queries.size(); ++idx) {
            int a = queries[idx][0];
            int b = queries[idx][1];
            if (a == b) {
                result[idx] = 0;
                continue;
            }
            int ia = i_to_idx[a];
            int ib = i_to_idx[b];
            if (prefix[ia] != prefix[ib]) {
                result[idx] = -1;
                continue;
            }
            if (ia > ib) {
                swap(ia, ib);
            }
            int curr = ia;
            int l = 0;
            for (int k = max_log - 1; k >= 0; --k) {
                if (P[k][curr] < ib) {
                    curr = P[k][curr];
                    l += (1 << k);
                }
            }
            result[idx] = l + 1;
        }

        return result;
    }
};

struct TestCase {
    int n;
    vector<int> nums;
    int maxDiff;
    vector<vector<int>> queries;
};

static inline long long runOnce(Solution& sol, vector<TestCase>& tests) {
    long long local_sum = 0;
    for (auto& t : tests) {
        vector<int> res = sol.pathExistenceQueries(t.n, t.nums, t.maxDiff, t.queries);
        for (int v : res) local_sum += v;
        local_sum += (long long)res.size();
    }
    return local_sum;
}

int main() {
    vector<TestCase> tests;

    // 1) Single node, self-query
    tests.push_back({
        1,
        {42},
        0,
        {{0, 0}}
    });

    // 2) Two nodes, large maxDiff allows connection
    tests.push_back({
        2,
        {1, 100},
        1000,
        {{0, 1}, {1, 0}, {0, 0}, {1, 1}}
    });

    // 3) Three nodes with chainable differences
    tests.push_back({
        3,
        {3, 1, 2},
        1,
        {{0, 1}, {1, 2}, {0, 2}, {2, 0}}
    });

    // 4) Four duplicates, zero maxDiff
    tests.push_back({
        4,
        {5, 5, 5, 5},
        0,
        {{0, 3}, {2, 1}, {0, 0}, {3, 2}}
    });

    // 5) Mixed negatives/positives, chainable by 5
    tests.push_back({
        5,
        {-5, 0, 5, 10, -10},
        5,
        {{0, 4}, {4, 2}, {1, 3}, {2, 2}}
    });

    // 6) Two separate clusters (0-2) and (100-102), maxDiff=1
    tests.push_back({
        6,
        {0, 1, 2, 100, 101, 102},
        1,
        {{0, 2}, {3, 5}, {0, 5}, {1, 4}}
    });

    // 7) Repeated blocks with zero maxDiff
    tests.push_back({
        5,
        {7, 7, 10, 10, 13},
        0,
        {{0, 1}, {2, 3}, {1, 2}, {3, 4}}
    });

    // 8) Zigzag values but all diffs <= 3 when sorted
    tests.push_back({
        7,
        {10, 8, 12, 6, 14, 4, 16},
        3,
        {{0, 6}, {1, 3}, {2, 4}, {5, 0}}
    });

    // 9) All equal values
    tests.push_back({
        8,
        {1, 1, 1, 1, 1, 1, 1, 1},
        0,
        {{0, 7}, {3, 4}, {6, 6}, {2, 5}}
    });

    // 10) Alternating values forming two clusters
    tests.push_back({
        9,
        {0, 5, 0, 5, 0, 5, 0, 5, 0},
        4,
        {{0, 2}, {1, 3}, {0, 1}, {7, 8}}
    });

    Solution sol;

    const int iterations = 1000;
    volatile long long sink = 0;

    auto start = chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        sink += runOnce(sol, tests);
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Checksum: " << sink << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}