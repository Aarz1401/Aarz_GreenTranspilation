#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>
#include <array>
#include <chrono>

using namespace std;
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
    // Define 10 diverse test inputs
    vector<Test> tests;

    // Test 1: Single node
    tests.push_back(Test{
        {},            // edges
        {5},           // nums
        1              // k
    });

    // Test 2: Two-node tree
    tests.push_back(Test{
        {{0,1}},
        {1, -1},
        1
    });

    // Test 3: Chain of 5
    tests.push_back(Test{
        {{0,1},{1,2},{2,3},{3,4}},
        {1,2,3,4,5},
        2
    });

    // Test 4: Star tree with 6 nodes
    tests.push_back(Test{
        {{0,1},{0,2},{0,3},{0,4},{0,5}},
        {-1,0,1,-2,2,3},
        3
    });

    // Test 5: Balanced binary tree with 7 nodes
    tests.push_back(Test{
        {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6}},
        {3,-2,5,1,-4,2,0},
        2
    });

    // Test 6: Random tree with large magnitudes
    tests.push_back(Test{
        {{0,1},{0,2},{1,3},{1,4},{2,5},{3,6},{4,7},{5,8},{6,9}},
        {1000000,-2000000,1500000,-1500000,500000,-500000,3000000,-1000000,2000000,-2500000},
        4
    });

    // Test 7: Tree with negatives and zeros
    tests.push_back(Test{
        {{0,1},{1,2},{1,3},{3,4},{4,5},{5,6},{2,7}},
        {-5,-3,-2,0,-1,-4,-6,-7},
        3
    });

    // Test 8: Chain with alternating big +/- values
    tests.push_back(Test{
        {{0,1},{1,2},{2,3},{3,4},{4,5},{5,6}},
        {100,-100,200,-200,300,-300,400},
        1
    });

    // Test 9: Larger balanced binary tree with 15 nodes
    {
        vector<vector<int>> edges9;
        for (int i = 1; i < 15; ++i) {
            edges9.push_back({(i - 1) / 2, i});
        }
        vector<int> nums9 = {1,-1,2,-2,3,-3,4,-4,5,-5,6,-6,7,-7,8};
        tests.push_back(Test{
            edges9,
            nums9,
            5
        });
    }

    // Test 10: Unbalanced tree with a branch
    tests.push_back(Test{
        {{0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{1,10},{10,11}},
        {9,-8,7,-6,5,-4,3,-2,1,0,2,-1},
        6
    });

    Solution sol;
    const int iterations = 1000;

    long long totalResult = 0;

    auto start = high_resolution_clock::now();

    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            totalResult += sol.subtreeInversionSum(tests[t].edges, tests[t].nums, tests[t].k);
        }
    }

    auto end = high_resolution_clock::now();
    auto ns = duration_cast<nanoseconds>(end - start).count();
    double ms = ns / 1e6;

    // Print totalResult to prevent optimization, and timing
    cout << "Total Result: " << totalResult << "\n";
    cout << "Time: " << ms << " ms" << endl;

    return 0;
}