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
#include <array>
#include <chrono>

using namespace std;

class UnionFind {
public:
    vector<int> parent;
    vector<int> rankv;
    UnionFind(int n) : parent(n), rankv(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find_set(int x) {
        while (parent[x] != x) { // path compression via path halving
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
    bool union_set(int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if (x == y) return false;
        if (rankv[x] > rankv[y]) swap(x, y);
        parent[x] = y;
        if (rankv[x] == rankv[y]) {
            rankv[y] += 1;
        }
        return true;
    }
};

class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        const int MOD = 1000000007;
        int n = static_cast<int>(edges.size()) + 1;
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0] - 1;
            int v = e[1] - 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int m = static_cast<int>(queries.size());
        vector<char> lookup(n, false);
        vector<vector<int>> lookup2(n);
        for (int i = 0; i < m; ++i) {
            for (int x : queries[i]) {
                lookup2[x - 1].push_back(i);
            }
        }
        UnionFind uf(n);
        vector<int> ancestor(n);
        iota(ancestor.begin(), ancestor.end(), 0);
        vector<int> dist(n, 0);
        vector<int> result(m, 0);

        struct Frame {
            int step;
            int a;
            int b;
        };
        vector<Frame> stk;
        stk.push_back({1, 0, 0});
        while (!stk.empty()) {
            Frame fr = stk.back();
            stk.pop_back();
            if (fr.step == 1) {
                int u = fr.a;
                for (int qi : lookup2[u]) {
                    if (!queries[qi].empty() && queries[qi][0] == queries[qi][1]) {
                        continue;
                    }
                    result[qi] += dist[u];
                    for (int x : queries[qi]) {
                        int xi = x - 1;
                        if (lookup[xi]) {
                            int rep = uf.find_set(xi);
                            result[qi] -= 2 * dist[ancestor[rep]];
                        }
                    }
                }
                lookup[u] = true;
                stk.push_back({2, u, 0});
            } else if (fr.step == 2) {
                int u = fr.a;
                int i = fr.b;
                if (i == (int)adj[u].size()) {
                    continue;
                }
                int v = adj[u][i];
                stk.push_back({2, u, i + 1});
                if (lookup[v]) {
                    continue;
                }
                dist[v] = dist[u] + 1;
                stk.push_back({3, v, u});
                stk.push_back({1, v, u});
            } else if (fr.step == 3) {
                int v = fr.a;
                int u = fr.b;
                uf.union_set(v, u);
                int rep = uf.find_set(u);
                ancestor[rep] = u;
            }
        }

        vector<int> POW2(max(0, n - 1), 1);
        for (int i = 0; i + 1 < (int)POW2.size(); ++i) {
            POW2[i + 1] = (int)((2LL * POW2[i]) % MOD);
        }

        vector<int> ans(m, 0);
        for (int i = 0; i < m; ++i) {
            int x = result[i];
            if (x - 1 >= 0) {
                ans[i] = POW2[x - 1];
            } else {
                ans[i] = 0;
            }
        }
        return ans;
    }
};

struct Test {
    vector<vector<int>> edges;
    vector<vector<int>> queries;
};
