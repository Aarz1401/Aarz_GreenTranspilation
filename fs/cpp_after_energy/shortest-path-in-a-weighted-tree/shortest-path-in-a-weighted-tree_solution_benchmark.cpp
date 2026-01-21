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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestInput> tests;
    tests.reserve(10);

    // Test 1: Small 2-node tree with multiple updates/queries
    {
        TestInput t;
        t.n = 2;
        t.edges = { {1, 2, 5} };
        t.queries = {
            {2, 1}, {2, 2},
            {1, 1, 2, 7}, {2, 2},
            {1, 1, 2, 3}, {2, 2}
        };
        tests.push_back(std::move(t));
    }

    // Test 2: Chain of 5 nodes
    {
        TestInput t;
        t.n = 5;
        for (int i = 1; i < t.n; ++i) {
            t.edges.push_back({i, i + 1, i}); // weights 1,2,3,4
        }
        t.queries = {
            {2, 5},
            {1, 2, 3, 10},
            {2, 5},
            {1, 4, 5, 1},
            {2, 3},
            {1, 1, 2, 5},
            {2, 5},
            {2, 1},
            {2, 4}
        };
        tests.push_back(std::move(t));
    }

    // Test 3: Star tree centered at 1
    {
        TestInput t;
        t.n = 7;
        for (int v = 2; v <= 7; ++v) {
            t.edges.push_back({1, v, 2 * (v - 1)}); // 2,4,6,8,10,12
        }
        t.queries = {
            {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7},
            {1, 1, 7, 3}, {2, 7},
            {1, 1, 2, 5}, {2, 2},
            {1, 1, 6, 1}, {2, 6},
            {2, 1}
        };
        tests.push_back(std::move(t));
    }

    // Test 4: Balanced binary tree with updates
    {
        TestInput t;
        t.n = 7;
        t.edges = {
            {1, 2, 3}, {1, 3, 5},
            {2, 4, 2}, {2, 5, 4},
            {3, 6, 6}, {3, 7, 8}
        };
        t.queries = {
            {2, 4}, {2, 5}, {2, 6}, {2, 7},
            {1, 2, 5, 10},
            {1, 1, 3, 7},
            {2, 5}, {2, 6}, {2, 7}
        };
        tests.push_back(std::move(t));
    }

    // Test 5: Deep chain with large weights
    {
        TestInput t;
        t.n = 10;
        for (int i = 1; i < t.n; ++i) {
            t.edges.push_back({i, i + 1, 100000 + i});
        }
        t.queries = {
            {2, 10},
            {1, 5, 6, 200000},
            {2, 10},
            {1, 1, 2, 50000},
            {2, 2}, {2, 10}
        };
        tests.push_back(std::move(t));
    }

    // Test 6: 1-indexed heap-like tree (n=15) with patterned weights
    {
        TestInput t;
        t.n = 15;
        for (int i = 2; i <= t.n; ++i) {
            int p = i / 2;
            int w = (i * 3) % 10 + 1;
            t.edges.push_back({p, i, w});
        }
        t.queries = {
            {2, 15}, {2, 8},
            {1, 7, 14, 9}, {2, 14},
            {1, 5, 10, 8}, {2, 10},
            {1, 1, 3, 5}, {2, 6}, {2, 15},
            {1, 2, 5, 7}, {2, 9}, {2, 12}
        };
        tests.push_back(std::move(t));
    }

    // Test 7: Mixed shape with repeated edge updates
    {
        TestInput t;
        t.n = 8;
        t.edges = {
            {1, 2, 1}, {1, 3, 2},
            {2, 4, 3}, {2, 5, 4},
            {3, 6, 5}, {6, 7, 6}, {6, 8, 7}
        };
        t.queries = {
            {2, 7},
            {1, 6, 7, 1}, {2, 7},
            {1, 6, 7, 10}, {2, 7},
            {1, 3, 6, 1},
            {2, 8}, {2, 5}
        };
        tests.push_back(std::move(t));
    }

    // Test 8: Star with only queries (no updates)
    {
        TestInput t;
        t.n = 5;
        t.edges = {
            {1, 2, 1}, {1, 3, 2}, {1, 4, 3}, {1, 5, 4}
        };
        t.queries = {
            {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}
        };
        tests.push_back(std::move(t));
    }

    // Test 9: Chain with all updates before queries
    {
        TestInput t;
        t.n = 6;
        t.edges = {
            {1, 2, 5}, {2, 3, 5}, {3, 4, 5}, {4, 5, 5}, {5, 6, 5}
        };
        t.queries = {
            {1, 2, 3, 1}, {1, 4, 5, 2}, {1, 1, 2, 3}, {1, 5, 6, 4}, {1, 3, 4, 5},
            {2, 6}, {2, 3}, {2, 5}, {2, 1}, {2, 2}
        };
        tests.push_back(std::move(t));
    }

    // Test 10: Random-ish tree with mixed queries/updates
    {
        TestInput t;
        t.n = 12;
        t.edges = {
            {1, 2, 3}, {1, 3, 1},
            {2, 4, 4}, {2, 5, 2},
            {3, 6, 7}, {3, 7, 5},
            {4, 8, 6}, {5, 9, 3},
            {6, 10, 2}, {7, 11, 4}, {7, 12, 8}
        };
        t.queries = {
            {2, 12}, {2, 11}, {2, 8},
            {1, 7, 12, 3}, {2, 12},
            {1, 1, 3, 2}, {1, 2, 5, 6},
            {2, 9}, {2, 3}, {2, 10}, {2, 5},
            {1, 6, 10, 5}, {2, 10},
            {1, 4, 8, 1}, {2, 8},
            {2, 1}
        };
        tests.push_back(std::move(t));
    }

    Solution solver;

    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            vector<int> res = solver.treeQueries(t.n, t.edges, t.queries);
            for (int v : res) {
                checksum += static_cast<unsigned long long>(v) * 1315423911ULL + static_cast<unsigned long long>(iter);
            }
            checksum += static_cast<unsigned long long>(res.size());
        }
    }
    auto end = chrono::high_resolution_clock::now();

    double elapsed_ms = chrono::duration<double, std::milli>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}