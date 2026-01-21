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
#include <chrono>

using namespace std;

class BIT { // 0-indexed Fenwick Tree for prefix sums
public:
    explicit BIT(int n) : n_(n), bit_(n + 1, 0LL) {}

    void add(int i, long long val) {
        for (i += 1; i <= n_; i += (i & -i)) {
            bit_[i] += val;
        }
    }

    long long query(int i) const {
        long long ret = 0;
        for (i += 1; i > 0; i -= (i & -i)) {
            ret += bit_[i];
        }
        return ret;
    }

private:
    int n_;
    vector<long long> bit_;
};

class Solution {
public:
    vector<int> treeQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int, long long>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0] - 1;
            int v = e[1] - 1;
            long long w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        vector<int> L(n, 0), R(n, 0);
        vector<long long> dist(n, 0), lookup(n, 0);

        // Iterative DFS to compute Euler tour indices L, R and initial distances
        int cnt = 0;
        struct Frame { int step, u, p; long long d; };
        vector<Frame> stk;
        stk.push_back({1, 0, -1, 0});
        while (!stk.empty()) {
            auto cur = stk.back(); stk.pop_back();
            if (cur.step == 1) {
                int u = cur.u, p = cur.p;
                long long d = cur.d;
                L[u] = cnt++;
                dist[u] = d;
                stk.push_back({2, u, 0, 0});
                for (const auto& [v, w] : adj[u]) {
                    if (v == p) continue;
                    lookup[v] = w;
                    stk.push_back({1, v, u, d + w});
                }
            } else {
                int u = cur.u;
                R[u] = cnt;
            }
        }

        BIT bit(n);
        vector<int> result;
        result.reserve(queries.size());
        for (const auto& q : queries) {
            if (q[0] == 1) {
                int u = q[1] - 1;
                int v = q[2] - 1;
                long long w = q[3];
                if (L[u] > L[v]) {
                    swap(u, v);
                }
                long long diff = w - lookup[v];
                bit.add(L[v], diff);
                bit.add(R[v], -diff);
                lookup[v] = w;
            } else {
                int x = q[1] - 1;
                long long res = dist[x] + bit.query(L[x]);
                result.push_back(static_cast<int>(res));
            }
        }
        return result;
    }
};

struct TestInput {
    int n;
    vector<vector<int>> edges;
    vector<vector<int>> queries;
};
