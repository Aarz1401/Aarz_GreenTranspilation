#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
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

int main() {
    vector<Test> tests;

    // Test 1: n=2, simple edge
    tests.push_back(Test{
        {{1,2}},
        {{1,2},{1,1},{2,2}}
    });

    // Test 2: n=5, star centered at 1
    tests.push_back(Test{
        {{1,2},{1,3},{1,4},{1,5}},
        {{2,3},{4,5},{1,1},{2,2},{3,5}}
    });

    // Test 3: n=6, chain
    tests.push_back(Test{
        {{1,2},{2,3},{3,4},{4,5},{5,6}},
        {{1,6},{2,5},{3,4},{1,3}}
    });

    // Test 4: n=7, balanced binary tree
    tests.push_back(Test{
        {{1,2},{1,3},{2,4},{2,5},{3,6},{3,7}},
        {{4,7},{5,6},{2,3},{4,5,6,7}}
    });

    // Test 5: n=8, mixed branching
    tests.push_back(Test{
        {{1,2},{2,3},{2,4},{4,5},{5,6},{5,7},{7,8}},
        {{1,8},{3,4},{6,8},{2,2},{4,7}}
    });

    // Test 6: n=1, single node
    tests.push_back(Test{
        {},
        {{1,1},{1,1}}
    });

    // Test 7: n=10, deeper tree
    tests.push_back(Test{
        {{1,2},{1,3},{2,4},{2,5},{3,6},{3,7},{7,8},{8,9},{9,10}},
        {{4,5},{6,7},{8,10},{1,10},{3,3}}
    });

    // Test 8: n=9, varied structure
    tests.push_back(Test{
        {{1,2},{2,3},{3,4},{4,5},{2,6},{6,7},{7,8},{7,9}},
        {{5,9},{1,4},{6,8},{2,2}}
    });

    // Test 9: n=4, star centered at 2 with repeated nodes in queries
    tests.push_back(Test{
        {{2,1},{2,3},{2,4}},
        {{2,2,2,2},{1,3,1,3},{1,4,2,2}}
    });

    // Test 10: n=3, small chain
    tests.push_back(Test{
        {{1,2},{2,3}},
        {{1,3},{1,2},{2,3},{3,3}}
    });

    using namespace std::chrono;
    volatile long long sink = 0; // volatile to prevent over-optimization

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto &t : tests) {
            Solution sol;
            auto res = sol.assignEdgeWeights(const_cast<vector<vector<int>>&>(t.edges),
                                             const_cast<vector<vector<int>>&>(t.queries));
            for (int v : res) sink += v;
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(end - start).count();

    cout << "Checksum: " << sink << "\n";
    cout << "Elapsed (ms): " << elapsed << "\n";
    return 0;
}