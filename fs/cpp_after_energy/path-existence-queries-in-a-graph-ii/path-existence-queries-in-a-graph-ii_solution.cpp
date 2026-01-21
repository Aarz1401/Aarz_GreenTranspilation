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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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
