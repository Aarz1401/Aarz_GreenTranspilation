#include <iostream>
#include <vector>
#include <tuple>
#include <utility>
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
            vector<char> visited(N, false);
            int root = 0;
            stk.push_back({1, root, -1});
            while (!stk.empty()) {
                Step cur = stk.back(); stk.pop_back();
                if (cur.type == 1) {
                    int u = cur.a;
                    if (visited[u]) continue;
                    visited[u] = true;
                    path.push_back(u);
                    for (const auto& it : lookup3[u]) {
                        int i = it.first, t = it.second;
                        int d = depth[u] - depth[lca[i]];
                        (void)t; // same handling for both sides since u is the attached endpoint
                        int j = binary_search_int(0, d, [&](int x) {
                            int idx = (int)path.size() - 1 - x;
                            return 2LL * (dist[u] - dist[path[idx]]) >= result[i];
                        });
                        int idx2 = (int)path.size() - 1 - j;
                        result2[i] = path[idx2];
                    }
                    stk.push_back({3, u, -1}); // post step to pop path
                    stk.push_back({2, u, 0});
                } else if (cur.type == 2) {
                    int u = cur.a;
                    int i = cur.b;
                    if (i == (int)adj[u].size()) continue;
                    auto [v, w] = adj[u][i];
                    (void)w;
                    stk.push_back({2, u, i + 1});
                    if (visited[v]) continue;
                    stk.push_back({1, v, u});
                } else if (cur.type == 3) {
                    path.pop_back();
                }
            }
            return result2;
        };

        auto tmp = iter_dfs();
        const auto& result = get<0>(tmp);
        const auto& lca = get<1>(tmp);
        const auto& dist = get<2>(tmp);
        const auto& depth = get<3>(tmp);
        vector<int> ans = iter_dfs2(result, lca, dist, depth);
        return ans;
    }
};

struct Test {
    int n;
    vector<vector<int>> edges;
    vector<vector<int>> queries;
};

int main() {
    vector<Test> tests;

    // 1) Single node
    tests.push_back({
        1,
        {},
        {{0,0}}
    });

    // 2) Two nodes
    tests.push_back({
        2,
        {{0,1,5}},
        {{0,1},{1,0},{0,0},{1,1}}
    });

    // 3) Three-node chain
    tests.push_back({
        3,
        {{0,1,2},{1,2,3}},
        {{0,2},{0,1},{1,2}}
    });

    // 4) Star with center 0
    tests.push_back({
        4,
        {{0,1,1},{0,2,2},{0,3,3}},
        {{1,2},{1,3},{2,3},{0,3}}
    });

    // 5) Chain with varied weights
    tests.push_back({
        5,
        {{0,1,1},{1,2,1},{2,3,10},{3,4,1}},
        {{0,4},{0,3},{2,4}}
    });

    // 6) Balanced-ish tree
    tests.push_back({
        6,
        {{0,1,4},{0,2,1},{1,3,2},{1,4,2},{2,5,7}},
        {{3,5},{4,5},{3,4},{2,5},{0,5}}
    });

    // 7) Unbalanced with a branch
    tests.push_back({
        7,
        {{0,1,1},{1,2,1},{2,3,1},{3,4,1},{4,5,10},{2,6,2}},
        {{6,5},{0,6},{1,4},{3,5}}
    });

    // 8) Larger branching
    tests.push_back({
        8,
        {{0,1,3},{0,2,5},{1,3,4},{1,4,6},{2,5,2},{5,6,1},{5,7,8}},
        {{3,7},{4,6},{6,7},{2,7}}
    });

    // 9) Long chain of 9
    tests.push_back({
        9,
        {{0,1,1},{1,2,1},{2,3,1},{3,4,1},{4,5,1},{5,6,1},{6,7,1},{7,8,1}},
        {{0,8},{2,6},{3,3},{1,7}}
    });

    // 10) Tree with varying weights
    tests.push_back({
        10,
        {{0,1,9},{0,2,3},{2,3,4},{2,4,5},{4,5,6},{4,6,7},{6,7,8},{6,8,2},{8,9,1}},
        {{1,9},{5,7},{3,5},{0,9},{2,6}}
    });

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<int> res = sol.findMedian(t.n, const_cast<vector<vector<int>>&>(t.edges), const_cast<vector<vector<int>>&>(t.queries));
            for (int x : res) checksum += x;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}