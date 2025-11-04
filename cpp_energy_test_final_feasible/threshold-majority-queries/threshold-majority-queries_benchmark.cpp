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

int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    // 1) All distinct elements
    tests.push_back({
        {1, 2, 3, 4, 5},
        {
            {0, 4, 1},
            {1, 3, 2},
            {2, 2, 1}
        }
    });

    // 2) All same elements
    tests.push_back({
        {7, 7, 7, 7, 7},
        {
            {0, 4, 3},
            {0, 4, 6},
            {2, 4, 1}
        }
    });

    // 3) Increasing frequency tail
    tests.push_back({
        {1,2,2,3,3,3,4,4,4,4},
        {
            {0, 9, 3},
            {0, 5, 2},
            {6, 9, 2}
        }
    });

    // 4) Negative numbers and zeros
    tests.push_back({
        {-5, -5, 0, 0, 0, -1, -1},
        {
            {0, 6, 2},
            {0, 1, 2},
            {5, 6, 2}
        }
    });

    // 5) INT limits
    tests.push_back({
        {INT_MIN, INT_MAX, INT_MIN, INT_MAX, INT_MAX},
        {
            {0, 4, 2},
            {0, 2, 2},
            {1, 3, 2}
        }
    });

    // 6) Alternating blocks
    tests.push_back({
        {1,1,2,2,1,1,2,2,1,1},
        {
            {0, 9, 3},
            {2, 7, 3},
            {3, 3, 1}
        }
    });

    // 7) Threshold t = 0 and mixed
    tests.push_back({
        {5, 6, 5, 6, 5},
        {
            {0, 4, 0},
            {1, 3, 1},
            {2, 2, 1}
        }
    });

    // 8) Single element array
    tests.push_back({
        {42},
        {
            {0, 0, 1},
            {0, 0, 2}
        }
    });

    // 9) Mixed blocks with various ranges
    tests.push_back({
        {1,2,3,4,5,5,5,6,7,7,8,8,8,8},
        {
            {0, 13, 4},
            {5, 10, 2},
            {10, 13, 3}
        }
    });

    // 10) Random small with multiple modes
    tests.push_back({
        {2,2,2,1,1,3,3,3,3,2,2,1},
        {
            {0, 11, 3},
            {0, 5, 3},
            {6, 9, 2},
            {9, 11, 2}
        }
    });

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::microseconds;

    Solution sol;
    volatile long long checksum = 0; // volatile to prevent optimization

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t ti = 0; ti < tests.size(); ++ti) {
            const auto& nums = tests[ti].nums;
            const auto& queries = tests[ti].queries;
            // Need non-const vectors because API expects non-const references
            vector<int> nums_copy = nums;
            vector<vector<int>> queries_copy = queries;
            vector<int> res = sol.subarrayMajority(nums_copy, queries_copy);
            // Accumulate checksum
            long long local = 0;
            for (int v : res) {
                local = (local * 1315423911LL) ^ (v + 0x9e3779b97f4a7c15ULL);
            }
            checksum ^= (local + (ti + 1) * 0x5851f42d4c957f2dULL);
        }
    }
    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed microseconds: " << elapsed_us << "\n";
    return 0;
}