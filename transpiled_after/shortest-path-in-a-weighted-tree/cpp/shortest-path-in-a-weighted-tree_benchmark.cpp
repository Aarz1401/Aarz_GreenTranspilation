#include <iostream>
#include <vector>
#include <algorithm>
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<TestInput> tests;

    // Test 1: Single node tree
    tests.push_back({
        1,
        {},
        {
            {2, 1}
        }
    });

    // Test 2: Two-node tree with update
    tests.push_back({
        2,
        {
            {1, 2, 5}
        },
        {
            {2, 2},
            {1, 1, 2, 7},
            {2, 2}
        }
    });

    // Test 3: Star-shaped tree
    tests.push_back({
        6,
        {
            {1, 2, 3}, {1, 3, 4}, {1, 4, 5}, {1, 5, 6}, {1, 6, 7}
        },
        {
            {2, 2}, {2, 3}, {2, 6},
            {1, 1, 4, 10}, {2, 4},
            {1, 1, 2, 2}, {2, 2}
        }
    });

    // Test 4: Line tree with negative update and reversed endpoints
    tests.push_back({
        5,
        {
            {1, 2, 1}, {2, 3, 2}, {3, 4, 3}, {4, 5, 4}
        },
        {
            {2, 5},
            {1, 4, 3, -1}, // update edge (3,4) using reversed order
            {2, 5},
            {1, 1, 2, 5},  // update (1,2)
            {2, 5}
        }
    });

    // Test 5: Balanced-ish tree with zero weights
    tests.push_back({
        7,
        {
            {1, 2, 0}, {1, 3, 5}, {2, 4, 0}, {2, 5, 1}, {3, 6, 2}, {3, 7, 0}
        },
        {
            {2, 4}, {2, 7},
            {1, 2, 5, 3}, // update (2,5) to 3
            {2, 5},
            {1, 3, 7, 4}, // update (3,7) to 4
            {2, 7}
        }
    });

    // Test 6: Random tree with multiple updates on same edge
    tests.push_back({
        8,
        {
            {1, 2, 3}, {1, 3, 1}, {2, 4, 4}, {2, 5, 2}, {3, 6, 7}, {6, 7, 5}, {6, 8, 6}
        },
        {
            {2, 7},
            {1, 6, 7, 10},
            {2, 7},
            {1, 6, 7, 5},
            {2, 7},
            {1, 2, 5, 1},
            {2, 5}
        }
    });

    // Test 7: Heavy weights within int range after sum
    tests.push_back({
        4,
        {
            {1, 2, 100000000}, {2, 3, 100000000}, {3, 4, 100000000}
        },
        {
            {2, 4},
            {1, 2, 3, 50000000},
            {2, 4}
        }
    });

    // Test 8: Negative weights and update to more negative
    tests.push_back({
        3,
        {
            {1, 2, -5}, {2, 3, -5}
        },
        {
            {2, 3},
            {2, 2},
            {1, 2, 3, -10},
            {2, 3}
        }
    });

    // Test 9: Mixed updates with reversed endpoint orders
    tests.push_back({
        5,
        {
            {1, 2, 2}, {2, 3, 3}, {2, 4, 4}, {1, 5, 1}
        },
        {
            {2, 3},
            {1, 3, 2, 10}, // update (2,3) via reversed order
            {2, 3},
            {1, 5, 1, 0},  // update (1,5) via reversed order
            {2, 5},
            {1, 4, 2, 1},  // update (2,4) via reversed order
            {2, 4}
        }
    });

    // Test 10: Chain with zeros, toggle updates
    tests.push_back({
        6,
        {
            {1, 2, 0}, {2, 3, 0}, {3, 4, 0}, {4, 5, 0}, {5, 6, 0}
        },
        {
            {2, 6},
            {1, 3, 4, 5},
            {2, 6},
            {1, 3, 4, 0},
            {2, 6},
            {1, 2, 3, 2},
            {2, 6}
        }
    });

    const int iterations = 1000;

    Solution sol;
    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            auto res = sol.treeQueries(t.n, t.edges, t.queries);
            for (int v : res) {
                checksum += static_cast<unsigned long long>(v);
                checksum ^= (checksum << 7) ^ (checksum >> 3);
            }
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}