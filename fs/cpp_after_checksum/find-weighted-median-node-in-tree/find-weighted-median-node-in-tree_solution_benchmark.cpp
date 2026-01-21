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
#include <functional>
#include <utility>
#include <chrono>
#include <cstdint>

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
                        int i = it.first;
                        int d = depth[u] - depth[lca[i]];
                        int j = binary_search_int(0, d, [&](int x) {
                            int idx = (int)path.size() - 1 - x;
                            return 2LL * (dist[u] - dist[path[idx]]) >= result[i];
                        });
                        int idx2 = (int)path.size() - 1 - j;
                        result2[i] = path[idx2];
                    }
                    stk.push_back({3, u, -1});
                    stk.push_back({2, u, 0});
                } else if (cur.type == 2) {
                    int u = cur.a;
                    int i = cur.b;
                    if (i == (int)adj[u].size()) continue;
                    auto [v, w] = adj[u][i];
                    stk.push_back({2, u, i + 1});
                    // Traverse only to children in the rooted tree (using depth info)
                    if (depth[v] > depth[u]) {
                        stk.push_back({1, v, -1});
                    }
                } else if (cur.type == 3) {
                    // Post-visit: pop current node from path
                    path.pop_back();
                }
            }
            return result2;
        };

        auto [result, lca, dist, depth] = iter_dfs();
        vector<int> med = iter_dfs2(result, lca, dist, depth);
        return med;
    }
};

struct TestCase {
    int n;
    vector<vector<int>> edges;
    vector<vector<int>> queries;
};

int main() {
    // Build 10 diverse test inputs
    vector<TestCase> tests;

    // 1) Single node, trivial queries
    {
        TestCase t;
        t.n = 1;
        t.edges = {};
        t.queries = {{0,0}, {0,0}};
        tests.push_back(t);
    }

    // 2) Two-node tree
    {
        TestCase t;
        t.n = 2;
        t.edges = {{0,1,5}};
        t.queries = {{0,1}, {1,0}, {0,0}, {1,1}};
        tests.push_back(t);
    }

    // 3) Star tree with center 0
    {
        TestCase t;
        t.n = 7;
        t.edges = {{0,1,3},{0,2,5},{0,3,2},{0,4,7},{0,5,11},{0,6,1}};
        t.queries = {{1,2},{3,4},{5,6},{1,6},{2,5},{3,0},{4,1},{2,3}};
        tests.push_back(t);
    }

    // 4) Path of length 10
    {
        TestCase t;
        t.n = 10;
        for (int i = 0; i < 9; ++i) t.edges.push_back({i, i+1, i+1});
        t.queries = {{0,9},{2,7},{8,4},{3,3},{9,1},{0,0},{5,9},{1,6}};
        tests.push_back(t);
    }

    // 5) Balanced-ish binary tree n=15
    {
        TestCase t;
        t.n = 15;
        for (int i = 0; i <= 6; ++i) {
            int l = 2*i+1, r = 2*i+2;
            if (l < t.n) t.edges.push_back({i, l, i+2});
            if (r < t.n) t.edges.push_back({i, r, i+3});
        }
        t.queries = {{14,0},{7,8},{10,11},{3,4},{13,9},{6,1},{2,14},{5,12},{0,0}};
        tests.push_back(t);
    }

    // 6) Random-like tree n=20 (fixed)
    {
        TestCase t;
        t.n = 20;
        t.edges = {
            {0,1,4},{0,2,8},{2,3,3},{1,4,7},{3,5,6},{2,6,5},{5,7,9},{4,8,2},{6,9,1},
            {7,10,4},{8,11,3},{9,12,8},{10,13,2},{11,14,7},{12,15,5},{13,16,4},{14,17,6},{15,18,3},{16,19,9}
        };
        t.queries = {{0,19},{4,14},{10,3},{12,7},{5,15},{11,6},{18,2},{9,9},{1,13},{8,0}};
        tests.push_back(t);
    }

    // 7) Heavy weights path n=8
    {
        TestCase t;
        t.n = 8;
        int w = 1000000000;
        for (int i = 0; i < 7; ++i) t.edges.push_back({i, i+1, w - (i*3)});
        t.queries = {{0,7},{1,6},{2,5},{3,4},{0,0},{7,7},{1,1}};
        tests.push_back(t);
    }

    // 8) Repeated queries on a moderate tree n=12
    {
        TestCase t;
        t.n = 12;
        t.edges = {
            {0,1,1},{0,2,2},{1,3,3},{1,4,4},{2,5,5},{2,6,6},
            {3,7,7},{4,8,8},{5,9,9},{6,10,10},{6,11,11}
        };
        t.queries = {{7,9},{7,9},{7,9},{8,10},{8,10},{3,11},{3,11},{0,11},{5,1},{2,8},{4,4}};
        tests.push_back(t);
    }

    // 9) Non-empty tree but zero queries
    {
        TestCase t;
        t.n = 5;
        t.edges = {{0,1,2},{1,2,3},{2,3,4},{3,4,5}};
        t.queries = {};
        tests.push_back(t);
    }

    // 10) Larger path n=50 with mixed queries
    {
        TestCase t;
        t.n = 50;
        for (int i = 0; i < 49; ++i) t.edges.push_back({i, i+1, (i%7)+1});
        t.queries = {
            {0,49},{10,40},{5,25},{12,12},{3,44},{7,33},{0,1},{1,2},{2,3},{3,4},
            {20,21},{21,22},{22,23},{23,24},{24,25},{25,26},{26,27},{27,28},{28,29},{30,35}
        };
        tests.push_back(t);
    }

    Solution sol;
    volatile uint64_t checksum = 0; // volatile to avoid optimization

    auto t1 = chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t ti = 0; ti < tests.size(); ++ti) {
            auto n = tests[ti].n;
            auto edges = tests[ti].edges;
            auto queries = tests[ti].queries;
            vector<int> res = sol.findMedian(n, edges, queries);
            // Accumulate into checksum
            checksum ^= (uint64_t)res.size() + (ti + 1);
            for (size_t i = 0; i < res.size(); ++i) {
                checksum = checksum * 1000003ULL + (uint64_t)(res[i] + 1) + (i + 1);
            }
        }
    }
    auto t2 = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}