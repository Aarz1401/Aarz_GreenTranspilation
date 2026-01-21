#include <vector>
#include <utility>
#include <algorithm>

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
    vector<TestInput> tests;

    // Test 1: Single node
    tests.push_back({
        1,
        {},
        { {2,1} }
    });

    // Test 2: Small chain with updates
    tests.push_back({
        3,
        { {1,2,5}, {2,3,7} },
        { {2,3}, {1,2,3,10}, {2,3}, {1,1,2,1}, {2,3}, {2,2}, {2,1} }
    });

    // Test 3: Star tree
    tests.push_back({
        5,
        { {1,2,1}, {1,3,2}, {1,4,3}, {1,5,4} },
        { {2,5}, {1,1,3,10}, {2,3}, {2,5}, {1,1,5,1}, {2,5}, {2,1} }
    });

    // Test 4: Balanced tree
    tests.push_back({
        7,
        { {1,2,3}, {1,3,4}, {2,4,5}, {2,5,6}, {3,6,7}, {3,7,8} },
        { {2,4}, {2,7}, {1,3,7,2}, {2,7}, {1,1,3,10}, {2,6}, {2,2}, {1,2,5,1}, {2,5} }
    });

    // Test 5: Random small tree with multiple updates
    tests.push_back({
        6,
        { {1,2,2}, {1,3,5}, {2,4,1}, {2,5,2}, {3,6,3} },
        { {2,6}, {1,1,3,1}, {2,6}, {1,2,5,10}, {2,5}, {1,2,4,5}, {2,4}, {2,3} }
    });

    // Test 6: Chain of 10 nodes with several updates
    tests.push_back({
        10,
        { {1,2,1}, {2,3,2}, {3,4,3}, {4,5,4}, {5,6,5}, {6,7,6}, {7,8,7}, {8,9,8}, {9,10,9} },
        { {2,10}, {1,5,6,10}, {2,10}, {1,1,2,0}, {2,1}, {2,2}, {2,3}, {1,9,10,1}, {2,10}, {2,5} }
    });

    // Test 7: Star with only queries
    tests.push_back({
        4,
        { {1,2,7}, {1,3,8}, {1,4,9} },
        { {2,2}, {2,3}, {2,4}, {2,1}, {2,3}, {2,2} }
    });

    // Test 8: Mixed weights with larger values
    tests.push_back({
        8,
        { {1,2,100}, {2,3,200}, {2,4,300}, {1,5,400}, {5,6,500}, {5,7,600}, {7,8,700} },
        { {2,8}, {1,5,7,1000}, {2,8}, {1,1,5,50}, {2,8}, {2,6}, {1,2,4,100}, {2,4} }
    });

    // Test 9: Complete binary tree up to 15
    tests.push_back({
        15,
        { {1,2,2}, {1,3,3}, {2,4,4}, {2,5,5}, {3,6,6}, {3,7,7}, {4,8,8}, {4,9,9},
          {5,10,10}, {5,11,11}, {6,12,12}, {6,13,13}, {7,14,14}, {7,15,15} },
        { {2,15}, {1,7,15,1}, {2,15}, {1,1,3,10}, {2,15}, {2,14}, {1,2,5,1}, {2,11} }
    });

    // Test 10: Random tree with repeated updates
    tests.push_back({
        9,
        { {1,2,5}, {1,3,2}, {3,4,4}, {3,5,1}, {2,6,3}, {6,7,6}, {6,8,2}, {8,9,7} },
        { {2,9}, {1,6,8,5}, {2,9}, {1,1,2,1}, {2,9}, {1,3,4,10}, {2,4}, {1,3,5,7}, {2,5}, {2,6} }
    });

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            Solution sol;
            vector<int> out = sol.treeQueries(t.n, t.edges, t.queries);
            DoNotOptimize(out); 
            //for (int v : out) checksum += v;
        }
        //sink = checksum;
    }

    return 0;
}