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
#include <tuple>
#include <functional>
#include <array>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}
using namespace std::chrono;

class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<array<long long, 2>> dp;
        function<tuple<long long, long long, long long>(int, int)> dfs =
            [&](int u, int p) -> tuple<long long, long long, long long> {
                dp.push_back({0LL, 0LL});
                long long total = nums[u];
                long long pos = 0, neg = 0;
                for (int v : adj[u]) {
                    if (v == p) continue;
                    auto [new_total, new_pos, new_neg] = dfs(v, u);
                    total += new_total;
                    pos += new_pos;
                    neg += new_neg;
                }
                pos = max(pos, dp.back()[1] - 2 * total);
                neg = max(neg, dp.back()[0] + 2 * total);
                dp.pop_back();
                if ((int)dp.size() - k >= 0) {
                    dp[dp.size() - k][0] += pos;
                    dp[dp.size() - k][1] += neg;
                }
                return {total, pos, neg};
            };

        auto [total, pos, neg] = dfs(0, -1);
        return total + pos;
    }
};

struct Test {
    vector<vector<int>> edges;
    vector<int> nums;
    int k;
};

int main() {
    vector<Test> tests;
    tests.reserve(10);

    // Test 1: Empty tree
    tests.push_back(Test{ {}, {}, 1 });

    // Test 2: Single node
    tests.push_back(Test{ {}, {5}, 1 });

    // Test 3: Two nodes
    tests.push_back(Test{ {{0,1}}, {1, -1}, 1 });

    // Test 4: Chain of 5 nodes
    {
        Test t;
        int n = 5;
        for (int i = 1; i < n; ++i) t.edges.push_back({i - 1, i});
        t.nums = {1, 2, 3, 4, 5};
        t.k = 2;
        tests.push_back(std::move(t));
    }

    // Test 5: Star tree with 6 nodes (0 center)
    {
        Test t;
        int n = 6;
        for (int i = 1; i < n; ++i) t.edges.push_back({0, i});
        t.nums = {-1, -2, -3, -4, -5, -6};
        t.k = 3;
        tests.push_back(std::move(t));
    }

    // Test 6: Balanced binary tree (7 nodes)
    {
        Test t;
        int n = 7;
        for (int i = 1; i < n; ++i) t.edges.push_back({(i - 1) / 2, i});
        t.nums = {3, -1, 4, -5, 2, 0, 7};
        t.k = 2;
        tests.push_back(std::move(t));
    }

    // Test 7: Custom shaped tree (10 nodes) with mixed values including large
    {
        Test t;
        t.edges = {
            {0,1}, {1,2}, {1,3}, {3,4}, {0,5}, {5,6}, {6,7}, {6,8}, {8,9}
        };
        t.nums = {10, -20, 35, -40, 15, 0, 7, 8, -9, 1000000000};
        t.k = 4;
        tests.push_back(std::move(t));
    }

    // Test 8: Longer chain (50 nodes) with alternating signs
    {
        Test t;
        int n = 50;
        for (int i = 1; i < n; ++i) t.edges.push_back({i - 1, i});
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i % 2 == 0) ? (i * 2) : (-i);
        t.k = 10;
        tests.push_back(std::move(t));
    }

    // Test 9: Random-like tree (100 nodes) with pseudo-random values
    {
        Test t;
        int n = 100;
        uint64_t seed = 88172645463393265ull;
        auto nextRand = [&seed]() -> uint64_t {
            seed = seed * 6364136223846793005ULL + 1ULL;
            return seed;
        };
        for (int i = 1; i < n; ++i) {
            int p = static_cast<int>(nextRand() % i);
            t.edges.push_back({p, i});
        }
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) {
            long long val = static_cast<long long>(nextRand() % 2000001ULL) - 1000000LL;
            t.nums[i] = static_cast<int>(val);
        }
        t.k = 7;
        tests.push_back(std::move(t));
    }

    // Test 10: Perfect binary tree (31 nodes) with alternating pattern
    {
        Test t;
        int n = 31;
        for (int i = 1; i < n; ++i) t.edges.push_back({(i - 1) / 2, i});
        t.nums.resize(n);
        for (int i = 0; i < n; ++i) t.nums[i] = (i % 3 == 0) ? (i) : (-(i % 11));
        t.k = 5;
        tests.push_back(std::move(t));
    }

    // Ensure exactly 10 tests
    if (tests.size() != 10) {
        cout << "Failed to prepare 10 tests\n";
        return 1;
    }

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            checksum += sol.subtreeInversionSum(t.edges, t.nums, t.k);
        }
    }

    auto end = high_resolution_clock::now();

    auto elapsed_ms = duration_cast<milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}