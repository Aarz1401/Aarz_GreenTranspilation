#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
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

volatile int sink = 0;

int main() {
    vector<Test> tests = {
        // 1) n=2 line
        { { {1,2} }, { {1,2}, {1,1} } },
        // 2) n=5 line
        { { {1,2},{2,3},{3,4},{4,5} }, { {1,5},{2,4},{3,3} } },
        // 3) n=6 star centered at 1
        { { {1,2},{1,3},{1,4},{1,5},{1,6} }, { {2,3},{4,5},{6,1} } },
        // 4) n=7 balanced binary tree
        { { {1,2},{1,3},{2,4},{2,5},{3,6},{3,7} }, { {4,5},{4,6},{7,7} } },
        // 5) n=8 mixed tree
        { { {1,2},{1,3},{3,4},{3,5},{2,6},{6,7},{5,8} }, { {7,8},{2,5},{4,6} } },
        // 6) n=10 mixed
        { { {1,2},{2,3},{2,4},{4,5},{4,6},{6,7},{3,8},{8,9},{9,10} }, { {1,10},{5,7},{3,6},{8,8} } },
        // 7) n=9 star centered at 5
        { { {5,1},{5,2},{5,3},{5,4},{5,6},{5,7},{5,8},{5,9} }, { {1,9},{2,7},{4,5} } },
        // 8) n=12 complex
        { { {1,2},{2,3},{3,4},{4,5},{3,6},{6,7},{2,8},{8,9},{5,10},{10,11},{11,12} }, { {7,9},{12,1},{6,10},{3,3} } },
        // 9) n=15 path
        { { {1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15} }, { {1,15},{5,10},{7,7},{2,14} } },
        // 10) n=13 balanced-ish
        { { {1,2},{1,3},{2,4},{2,5},{3,6},{3,7},{4,8},{4,9},{5,10},{5,11},{6,12},{6,13} }, { {8,9},{8,13},{10,11},{12,1} } }
    };

    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            vector<int> out = sol.assignEdgeWeights(t.edges, t.queries);
            for (int v : out) checksum += v;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}