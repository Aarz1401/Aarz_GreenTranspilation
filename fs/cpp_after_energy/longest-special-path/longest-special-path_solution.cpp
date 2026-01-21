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
#include <utility>
#include <functional>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], l = e[2];
            adj[u].emplace_back(v, l);
            adj[v].emplace_back(u, l);
        }

        unordered_map<int, int> lookup;  // key: nums[u]-1 -> last depth
        vector<long long> prefix(1, 0);  // prefix[depth]
        pair<long long, int> res = {LLONG_MAX / 4, INT_MAX / 4};

        function<void(int, int, int, int)> dfs = [&](int u, int p, int d, int left) {
            int key = nums[u] - 1;
            int prev_d = -1;
            auto it = lookup.find(key);
            if (it != lookup.end()) prev_d = it->second;
            lookup[key] = d;

            left = max(left, prev_d);
            long long cur_len = prefix[d] - prefix[left + 1];
            pair<long long, int> cand = { -cur_len, d - left };
            if (cand < res) res = cand;

            for (const auto& [v, w] : adj[u]) {
                if (v == p) continue;
                prefix.push_back(prefix.back() + w);
                dfs(v, u, d + 1, left);
                prefix.pop_back();
            }

            if (prev_d == -1) lookup.erase(key);
            else lookup[key] = prev_d;
        };

        if (n > 0) {
            dfs(0, -1, 0, -1);
        }

        return { static_cast<int>(-res.first), res.second };
    }
};
