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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    // Prepare 10 diverse test cases
    vector<Test> tests;

    // 1) Single node tree, self queries
    {
        Test t;
        t.edges = {}; // n = 1
        t.queries = {{1,1}, {1,1}, {1,1}};
        tests.push_back(t);
    }

    // 2) Two-node tree with various pairs
    {
        Test t;
        t.edges = {{1,2}};
        t.queries = {{1,2}, {2,1}, {1,1}, {2,2}, {1,2}};
        tests.push_back(t);
    }

    // 3) Chain of 5 nodes
    {
        Test t;
        t.edges = {{1,2},{2,3},{3,4},{4,5}};
        t.queries = {{1,5}, {2,4}, {3,5}, {1,3}, {2,5}};
        tests.push_back(t);
    }

    // 4) Star with 6 nodes centered at 1
    {
        Test t;
        t.edges = {{1,2},{1,3},{1,4},{1,5},{1,6}};
        t.queries = {{2,3}, {4,6}, {2,5}, {1,3}, {5,5}};
        tests.push_back(t);
    }

    // 5) Balanced-ish binary tree with 7 nodes
    {
        Test t;
        t.edges = {{1,2},{1,3},{2,4},{2,5},{3,6},{3,7}};
        t.queries = {{4,5}, {4,6}, {2,3}, {7,7}, {5,6}, {1,7}, {4,7}};
        tests.push_back(t);
    }

    // 6) Unbalanced tree with 10 nodes
    {
        Test t;
        t.edges = {{1,2},{2,3},{3,4},{4,5},{5,6},{3,7},{7,8},{2,9},{9,10}};
        t.queries = {{1,6}, {8,10}, {4,7}, {2,8}, {6,9}, {1,10}, {5,5}};
        tests.push_back(t);
    }

    // 7) Long chain with 15 nodes
    {
        Test t;
        for (int i = 1; i < 15; ++i) t.edges.push_back({i, i+1});
        t.queries = {{1,15}, {1,8}, {7,14}, {3,12}, {5,5}, {2,13}, {4,11}};
        tests.push_back(t);
    }

    // 8) Tree with 4 nodes but empty queries
    {
        Test t;
        t.edges = {{1,2},{2,3},{2,4}};
        t.queries = {};
        tests.push_back(t);
    }

    // 9) Multi-level tree with 8 nodes
    {
        Test t;
        t.edges = {{1,2},{1,3},{2,4},{2,5},{3,6},{6,7},{6,8}};
        t.queries = {{4,5}, {4,6}, {7,8}, {3,5}, {2,8}, {1,7}, {5,7}};
        tests.push_back(t);
    }

    // 10) Larger tree with 20 nodes
    {
        Test t;
        t.edges = {
            {1,2},{1,3},{2,4},{2,5},{3,6},{3,7},
            {4,8},{5,9},{5,10},{6,11},{7,12},{7,13},
            {8,14},{9,15},{10,16},{11,17},{12,18},{13,19},{14,20}
        };
        t.queries = {
            {14,20}, {15,16}, {17,18}, {19,4}, {10,12}, {2,20}, {6,13}, {1,11}, {3,15}, {8,18}
        };
        tests.push_back(t);
    }

    // Benchmark
    using namespace std::chrono;
    int64_t checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            Solution sol;
            vector<vector<int>> edges = t.edges;
            vector<vector<int>> queries = t.queries;
            vector<int> ans = sol.assignEdgeWeights(edges, queries);
            checksum += static_cast<int64_t>(ans.size());
            for (size_t i = 0; i < ans.size(); ++i) {
                checksum += ans[i];
                checksum ^= (checksum << 7) ^ (checksum >> 3); // mix a bit
            }
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_ms = duration_cast<milliseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}