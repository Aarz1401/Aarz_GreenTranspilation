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
