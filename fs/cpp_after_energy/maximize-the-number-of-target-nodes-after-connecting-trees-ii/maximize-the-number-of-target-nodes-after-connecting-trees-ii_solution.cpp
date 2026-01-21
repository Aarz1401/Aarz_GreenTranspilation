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
#include <chrono>
#include <cstdint>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}
using namespace std::chrono;

// Time:  O(n + m)
// Space: O(n + m)

// bfs
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        auto find_adj = [&](const vector<vector<int>>& edges) {
            int n = static_cast<int>(edges.size()) + 1;
            vector<vector<int>> adj(n);
            for (const auto& e : edges) {
                int u = e[0], v = e[1];
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            return adj;
        };

        auto bfs = [&](const vector<vector<int>>& adj) {
            int n = static_cast<int>(adj.size());
            vector<int> lookup(n, -1);
            int parity = 0;
            vector<int> q = {0};
            lookup[0] = parity;
            while (!q.empty()) {
                vector<int> new_q;
                for (int u : q) {
                    for (int v : adj[u]) {
                        if (lookup[v] != -1) {
                            continue;
                        }
                        lookup[v] = parity ^ 1;
                        new_q.push_back(v);
                    }
                }
                q.swap(new_q);
                parity ^= 1;
            }
            int cnt = 0;
            for (int x : lookup) {
                if (x != -1) cnt += x;
            }
            vector<int> res(n);
            for (int u = 0; u < n; ++u) {
                res[u] = lookup[u] ? cnt : (n - cnt);
            }
            return res;
        };

        vector<vector<int>> adj2 = find_adj(edges2);
        vector<int> b2 = bfs(adj2);
        int mx = *max_element(b2.begin(), b2.end());
        vector<vector<int>> adj1 = find_adj(edges1);
        vector<int> b1 = bfs(adj1);
        for (int& x : b1) {
            x += mx;
        }
        return b1;
    }
};
