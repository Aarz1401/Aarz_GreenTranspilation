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
#include <numeric>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    vector<int> subarrayMajority(vector<int>& nums, vector<vector<int>>& queries) {
        // coordinate compression
        vector<int> sorted_nums = nums;
        sort(sorted_nums.begin(), sorted_nums.end());
        sorted_nums.erase(unique(sorted_nums.begin(), sorted_nums.end()), sorted_nums.end());
        unordered_map<int, int> num_to_idx;
        num_to_idx.reserve(sorted_nums.size() * 2);
        for (int i = 0; i < (int)sorted_nums.size(); ++i) {
            num_to_idx[sorted_nums[i]] = i;
        }
        int n = nums.size();
        int m = sorted_nums.size();
        vector<int> comp(n);
        for (int i = 0; i < n; ++i) {
            comp[i] = num_to_idx[nums[i]];
        }

        // Mo's algorithm
        int q = queries.size();
        vector<int> result(q, -1);
        vector<int> cnt(m, 0);
        vector<int> cnt2(n + 1, 0);
        int max_freq = 0;
        int block_size = static_cast<int>(sqrt(n)) + 1;

        vector<int> ord(q);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int a, int b) {
            int ba = queries[a][0] / block_size;
            int bb = queries[b][0] / block_size;
            if (ba != bb) return ba < bb;
            if (ba & 1) return queries[a][1] < queries[b][1];
            return queries[a][1] > queries[b][1];
        });

        auto add = [&](int i) {
            int idx = comp[i];
            if (cnt[idx]) {
                cnt2[cnt[idx]] -= 1;
            }
            cnt[idx] += 1;
            cnt2[cnt[idx]] += 1;
            if (cnt[idx] > max_freq) {
                max_freq = cnt[idx];
            }
        };

        auto remove = [&](int i) {
            int idx = comp[i];
            cnt2[cnt[idx]] -= 1;
            if (cnt2[max_freq] == 0) {
                --max_freq;
            }
            cnt[idx] -= 1;
            if (cnt[idx]) {
                cnt2[cnt[idx]] += 1;
            }
        };

        auto get_ans = [&](int t) -> int {
            if (max_freq < t) return -1;
            for (int i = 0; i < m; ++i) {
                if (cnt[i] == max_freq) {
                    return sorted_nums[i];
                }
            }
            return -1;
        };

        int left = 0, right = -1;
        for (int id : ord) {
            int l = queries[id][0];
            int r = queries[id][1];
            int t = queries[id][2];
            while (left > l) {
                --left;
                add(left);
            }
            while (right < r) {
                ++right;
                add(right);
            }
            while (left < l) {
                remove(left);
                ++left;
            }
            while (right > r) {
                remove(right);
                --right;
            }
            result[id] = get_ans(t);
        }

        return result;
    }
};

struct TestCase {
    vector<int> nums;
    vector<vector<int>> queries;
};
