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
#include <chrono>
#include <utility>
#include <tuple>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) : parent(n), rank_(n, 0) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find_set(int x) {
        int r = x;
        while (parent[r] != r) {
            r = parent[r];
        }
        // Path compression
        while (parent[x] != x) {
            int p = parent[x];
            parent[x] = r;
            x = p;
        }
        return r;
    }

    bool union_set(int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if (x == y) return false;
        if (rank_[x] > rank_[y]) {
            parent[x] = y;
        } else if (rank_[x] < rank_[y]) {
            parent[y] = x;
        } else {
            parent[x] = y;
            rank_[y] += 1;
        }
        return true;
    }

private:
    vector<int> parent;
    vector<int> rank_;
};

template <class F>
int binary_search_int(int left, int right, F check) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (check(mid)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

class Solution {
public:
    vector<int> findMedian(int n, vector<vector<int>>& edges, vector<vector<int>>& queries) {
        vector<vector<pair<int, long long>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            long long w = static_cast<long long>(e[2]);
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        auto iter_dfs = [&](void) {
            int N = n;
            int Q = (int)queries.size();
            vector<char> lookup(N, false);
            vector<vector<int>> lookup2(N);
            for (int i = 0; i < Q; ++i) {
                for (int t = 0; t < 2; ++t) {
                    int x = queries[i][t];
                    lookup2[x].push_back(i);
                }
            }
            UnionFind uf(N);
            vector<int> ancestor(N);
            for (int i = 0; i < N; ++i) ancestor[i] = i;
            vector<int> depth(N, 0);
            vector<long long> dist(N, 0);
            vector<int> lca(Q, 0);
            vector<long long> result(Q, 0);

            struct Step { int type; int a; int b; };
            vector<Step> stk;
            int root = 0;
            stk.push_back({1, root, -1});
            while (!stk.empty()) {
                Step cur = stk.back(); stk.pop_back();
                if (cur.type == 1) {
                    int u = cur.a;
                    for (int i : lookup2[u]) {
                        if (queries[i][0] == queries[i][1]) {
                            lca[i] = u;
                            continue;
                        }
                        result[i] += dist[u];
                        for (int k = 0; k < 2; ++k) {
                            int x = queries[i][k];
                            if (lookup[x]) {
                                int fx = uf.find_set(x);
                                lca[i] = ancestor[fx];
                                result[i] -= 2LL * dist[lca[i]];
                            }
                        }
                    }
                    lookup[u] = true;
                    stk.push_back({2, u, 0});
                } else if (cur.type == 2) {
                    int u = cur.a;
                    int i = cur.b;
                    if (i == (int)adj[u].size()) continue;
                    auto [v, w] = adj[u][i];
                    stk.push_back({2, u, i + 1});
                    if (lookup[v]) continue;
                    dist[v] = dist[u] + w;
                    depth[v] = depth[u] + 1;
                    stk.push_back({3, v, u});
                    stk.push_back({1, v, u});
                } else if (cur.type == 3) {
                    int v = cur.a, u = cur.b;
                    uf.union_set(v, u);
                    ancestor[uf.find_set(u)] = u;
                }
            }
            return tuple<vector<long long>, vector<int>, vector<long long>, vector<int>>(result, lca, dist, depth);
        };

        auto iter_dfs2 = [&](const vector<long long>& result,
                             const vector<int>& lca,
                             vector<long long> dist,
                             vector<int> depth) {
            int N = n;
            int Q = (int)queries.size();
            vector<vector<pair<int, int>>> lookup3(N);
            for (int i = 0; i < Q; ++i) {
                int u = queries[i][0], v = queries[i][1];
                if (2LL * (dist[u] - dist[lca[i]]) >= result[i]) {
                    lookup3[u].emplace_back(i, 0);
                } else {
                    lookup3[v].emplace_back(i, 1);
                }
            }
            vector<int> result2(Q, 0);
            vector<int> path;

            struct Step { int type; int a; int b; };
            vector<Step> stk;
            int root = 0;
            stk.push_back({1, root, -1});
            while (!stk.empty()) {
                Step cur = stk.back(); stk.pop_back();
                if (cur.type == 1) {
                    int u = cur.a;
                    path.push_back(u);
                    for (const auto& it : lookup3[u]) {
                        int i = it.first, t = it.second;
                        int d = depth[u] - depth[lca[i]];
                        if (t == 0) {
                            int j = binary_search_int(0, d, [&](int x) {
                                int idx = (int)path.size() - 1 - x;
                                return 2LL * (dist[u] - dist[path[idx]]) >= result[i];
                            });
                            int idx2 = (int)path.size() - 1 - j;
                            result2[i] = path[idx2];
                        } else {
                            long long l = dist[queries[i][0]] - dist[lca[i]];
                            int j = binary_search_int(0, d - 1, [&](int x) {
                                int idx = (int)path.size() - d + x;
                                return 2LL * (l + (dist[path[idx]] - dist[lca[i]])) >= result[i];
                            });
                            int idx2 = (int)path.size() - d + j;
                            result2[i] = path[idx2];
                        }
                    }
                    stk.push_back({3, -1, -1});
                    stk.push_back({2, u, 0});
                } else if (cur.type == 2) {
                    int u = cur.a;
                    int i = cur.b;
                    if (i == (int)adj[u].size()) continue;
                    auto [v, w] = adj[u][i];
                    stk.push_back({2, u, i + 1});
                    if (path.size() >= 2 && path[path.size() - 2] == v) continue;
                    dist[v] = dist[u] + w;
                    depth[v] = depth[u] + 1;
                    stk.push_back({1, v, u});
                } else if (cur.type == 3) {
                    path.pop_back();
                }
            }
            return result2;
        };

        auto [result, lca, dist, depth] = iter_dfs();
        return iter_dfs2(result, lca, dist, depth);
    }
};

struct TestCase {
    int n;
    vector<vector<int>> edges;   // Each edge: {u, v, w}
    vector<vector<int>> queries; // Each query: {u, v}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;

    // 1) Chain of 5 nodes with increasing weights
    tests.push_back({
        5,
        {{0,1,1},{1,2,2},{2,3,3},{3,4,4}},
        {{0,4},{1,3},{2,2},{4,0}}
    });

    // 2) Star tree centered at 0
    tests.push_back({
        7,
        {{0,1,5},{0,2,1},{0,3,9},{0,4,2},{0,5,7},{0,6,3}},
        {{1,2},{3,4},{5,6},{1,0}}
    });

    // 3) Balanced binary tree with 7 nodes
    tests.push_back({
        7,
        {{0,1,4},{0,2,6},{1,3,3},{1,4,5},{2,5,2},{2,6,8}},
        {{3,4},{3,5},{5,6},{4,6}}
    });

    // 4) Unbalanced path with zero-weight edges
    tests.push_back({
        6,
        {{0,1,0},{1,2,0},{2,3,10},{3,4,0},{4,5,1}},
        {{0,5},{1,4},{2,2},{3,5}}
    });

    // 5) Single node tree
    tests.push_back({
        1,
        {},
        {{0,0},{0,0}}
    });

    // 6) Small tree with very large but 32-bit-safe weights
    tests.push_back({
        4,
        {{0,1,1000000000},{1,2,1000000000},{1,3,999999999}},
        {{2,3},{0,3},{0,2}}
    });

    // 7) Mixed branching tree
    tests.push_back({
        9,
        {{0,1,2},{1,2,2},{1,3,7},{3,4,1},{3,5,1},{0,6,3},{6,7,3},{6,8,3}},
        {{2,4},{7,8},{2,8},{5,8},{0,4}}
    });

    // 8) Deep path with a heavy branch
    tests.push_back({
        8,
        {{0,1,1},{1,2,1},{2,3,1},{3,4,10},{4,5,10},{5,6,10},{3,7,100}},
        {{0,6},{0,7},{2,5},{1,4}}
    });

    // 9) Chain with alternating large/small weights
    tests.push_back({
        10,
        {{0,1,1},{1,2,1000},{2,3,1},{3,4,1000},{4,5,1},{5,6,1000},{6,7,1},{7,8,1000},{8,9,1}},
        {{0,9},{0,5},{4,9},{3,7}}
    });

    // 10) Larger binary tree with 15 nodes
    tests.push_back({
        15,
        {
            {0,1,1},{0,2,2},
            {1,3,3},{1,4,4},
            {2,5,5},{2,6,6},
            {3,7,7},{3,8,8},
            {4,9,9},{4,10,10},
            {5,11,11},{5,12,12},
            {6,13,13},{6,14,14}
        },
        {{7,8},{7,14},{9,11},{10,13},{12,14},{0,14}}
    });

    Solution sol;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    long long checksum = 0;
    volatile long long volatile_sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        TestCase& tc = tests[iter % tests.size()];
        vector<int> ans = sol.findMedian(tc.n, tc.edges, tc.queries);
        for (int v : ans) checksum += v;
        checksum += (long long)ans.size();
    }

    auto end = high_resolution_clock::now();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    volatile_sink = checksum; // prevent optimization

    cout << "Checksum: " << volatile_sink << "\n";
    cout << "Time (ns): " << duration_ns << "\n";

    return 0;
}