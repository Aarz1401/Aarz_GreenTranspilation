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

static vector<vector<int>> genQueries(int n, int q, uint32_t seed) {
    vector<vector<int>> res;
    res.reserve(q);
    uint32_t x = seed;
    auto step = [&x]() {
        x = x * 1664525u + 1013904223u;
        return x;
    };
    for (int k = 0; k < q; ++k) {
        int l = static_cast<int>(step() % n);
        int r = l + static_cast<int>(step() % (n - l));
        int len = r - l + 1;
        int t = 1 + static_cast<int>(step() % (len + 3)); // sometimes > len to produce -1
        res.push_back({l, r, t});
    }
    return res;
}

int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1: All equal elements
    {
        TestCase tc;
        tc.nums = {1, 1, 1, 1};
        tc.queries = {
            {0, 3, 1},
            {0, 3, 4},
            {1, 2, 2},
            {2, 3, 3}
        };
        tests.push_back(move(tc));
    }

    // Test 2: All distinct
    {
        TestCase tc;
        tc.nums.resize(10);
        iota(tc.nums.begin(), tc.nums.end(), 1);
        tc.queries = {
            {0, 9, 1},
            {0, 9, 2},
            {3, 7, 1},
            {2, 2, 1},
            {5, 9, 3}
        };
        tests.push_back(move(tc));
    }

    // Test 3: Alternating two values
    {
        TestCase tc;
        tc.nums.resize(20);
        for (int i = 0; i < 20; ++i) tc.nums[i] = (i % 2 == 0) ? 2 : 3;
        tc.queries = {
            {0, 19, 6},
            {0, 19, 11},
            {2, 10, 3},
            {5, 15, 4},
            {0, 1, 1},
            {0, 0, 1}
        };
        tests.push_back(move(tc));
    }

    // Test 4: Negative values and mixed frequencies
    {
        TestCase tc;
        tc.nums = {-5, -5, -5, -1, -1, 0, 0, 0, 0, 10, -5};
        tc.queries = {
            {0, 10, 3},
            {3, 9, 3},
            {5, 8, 2},
            {0, 4, 3},
            {0, 10, 6},
            {10, 10, 1},
            {1, 1, 2}
        };
        tests.push_back(move(tc));
    }

    // Test 5: Generated pattern, size 100
    {
        TestCase tc;
        tc.nums.resize(100);
        for (int i = 0; i < 100; ++i) tc.nums[i] = ((i * 17 + 13) % 25) - 12;
        tc.queries = genQueries(100, 50, 12345u);
        tests.push_back(move(tc));
    }

    // Test 6: Repeated structural pattern, size 120
    {
        TestCase tc;
        tc.nums.resize(120);
        for (int i = 0; i < 120; ++i) {
            if (i % 6 == 0) tc.nums[i] = 5;
            else if (i % 3 == 0) tc.nums[i] = 3;
            else if (i % 2 == 0) tc.nums[i] = 2;
            else tc.nums[i] = 1;
        }
        tc.queries = genQueries(120, 60, 54321u);
        tests.push_back(move(tc));
    }

    // Test 7: Skewed distribution with heavy majority
    {
        TestCase tc;
        tc.nums.resize(150, 7);
        for (int i = 0; i < 150; ++i) {
            if (i % 10 == 0) tc.nums[i] = i;   // noise
            if (i % 7 == 3) tc.nums[i] = 3;    // more noise
        }
        tc.queries = genQueries(150, 70, 99991u);
        tests.push_back(move(tc));
    }

    // Test 8: Larger mixed values
    {
        TestCase tc;
        tc.nums.resize(250);
        for (int i = 0; i < 250; ++i) tc.nums[i] = ((i * 37) % 100) - 50;
        tc.queries = genQueries(250, 120, 424242u);
        tests.push_back(move(tc));
    }

    // Test 9: Sorted ascending
    {
        TestCase tc;
        tc.nums.resize(60);
        iota(tc.nums.begin(), tc.nums.end(), 0);
        tc.queries = genQueries(60, 30, 777u);
        tests.push_back(move(tc));
    }

    // Test 10: Sorted descending
    {
        TestCase tc;
        tc.nums.resize(60);
        for (int i = 0; i < 60; ++i) tc.nums[i] = 60 - i;
        tc.queries = genQueries(60, 30, 888u);
        tests.push_back(move(tc));
    }

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    uint64_t checksum = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        Solution solver;
        for (size_t ti = 0; ti < tests.size(); ++ti) {
            vector<int> ans = solver.subarrayMajority(tests[ti].nums, tests[ti].queries);
            for (size_t i = 0; i < ans.size(); ++i) {
                checksum += static_cast<uint64_t>(ans[i]) * 1315423911u + (ti * 104729u + i);
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed(ns): " << elapsed_ns << "\n";

    return 0;
}