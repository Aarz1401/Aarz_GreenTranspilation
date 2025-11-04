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

using namespace std;
using namespace std::chrono;

class UnionFind {
public:
    vector<int> parent;
    vector<int> rankv;
    UnionFind(int n) : parent(n), rankv(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find_set(int x) {
        if (parent[x] == x) return x;
        parent[x] = find_set(parent[x]);
        return parent[x];
    }
    bool union_set(int x, int y) {
        x = find_set(x);
        y = find_set(y);
        if (x == y) return false;
        if (rankv[x] < rankv[y]) {
            swap(x, y);
        }
        parent[y] = x;
        if (rankv[x] == rankv[y]) {
            rankv[x] += 1;
        }
        return true;
    }
};

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        UnionFind uf(n);
        int cnt = 0;
        long long INF = (long long)4e18;
        long long result = INF;
        for (const auto& e : edges) {
            int u = e[0], v = e[1], s = e[2], m = e[3];
            if (!m) continue;
            if (!uf.union_set(u, v)) {
                return -1;
            }
            cnt += 1;
            result = min(result, (long long)s);
        }
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] > b[2];
        });
        for (const auto& e : edges) {
            int u = e[0], v = e[1], s = e[2], m = e[3];
            if (m) continue;
            if (!uf.union_set(u, v)) continue;
            cnt += 1;
            if (cnt == (n - 1) - k) {
                result = min(result, (long long)s);
            } else if (cnt == n - 1) {
                result = min(result, 2LL * s);
            }
        }
        if (cnt != n - 1) return -1;
        return (int)result;
    }
};

struct TestCase {
    int n;
    vector<vector<int>> edges;
    int k;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;

    // 1) Required edges already form a spanning tree
    tests.push_back(TestCase{
        4,
        {
            {0,1,5,1}, {1,2,7,1}, {2,3,6,1},
            {0,3,10,0}, {1,3,4,0}
        },
        0
    });

    // 2) Required edges contain a cycle -> immediate -1
    tests.push_back(TestCase{
        4,
        {
            {0,1,3,1}, {1,2,4,1}, {2,0,5,1},
            {2,3,6,0}
        },
        1
    });

    // 3) No required edges; k = 0; connected via optional edges
    tests.push_back(TestCase{
        4,
        {
            {0,1,9,0}, {1,2,8,0}, {2,3,7,0}, {0,3,6,0}, {1,3,5,0}
        },
        0
    });

    // 4) No required edges; k = 2; both thresholds should be reached
    tests.push_back(TestCase{
        5,
        {
            {0,1,9,0}, {1,2,8,0}, {2,3,7,0}, {3,4,6,0},
            {0,2,5,0}, {1,3,4,0}, {0,4,3,0}
        },
        2
    });

    // 5) Disconnected graph -> -1
    tests.push_back(TestCase{
        5,
        {
            {0,1,5,0}, {1,2,5,0}, {3,4,5,0}
        },
        1
    });

    // 6) k > n-1; only final 2*s will be used
    tests.push_back(TestCase{
        4,
        {
            {0,1,8,0}, {1,2,7,0}, {2,3,6,0}
        },
        10
    });

    // 7) Mix of required and optional edges; k = 1
    tests.push_back(TestCase{
        5,
        {
            {0,1,6,1}, {1,2,9,1},
            {2,3,5,0}, {3,4,8,0}, {0,4,7,0}, {2,4,2,0}
        },
        1
    });

    // 8) Duplicate edge (required and optional); k = 0
    tests.push_back(TestCase{
        4,
        {
            {0,1,3,1},
            {0,1,10,0}, {1,2,4,0}, {2,3,6,0}, {0,3,5,0}
        },
        0
    });

    // 9) Zero weights involved; doubling zero remains zero
    tests.push_back(TestCase{
        3,
        {
            {0,1,0,0}, {1,2,0,0}, {0,2,1,0}
        },
        1
    });

    // 10) Larger small graph with mix of required and optional; k = 0
    tests.push_back(TestCase{
        7,
        {
            {0,1,5,1}, {1,2,7,1}, {2,3,6,1},
            {3,4,9,0}, {4,5,4,0}, {5,6,8,0}, {0,6,3,0}, {1,3,2,0}
        },
        0
    });

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;

    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            vector<vector<int>> edgesCopy = t.edges; // copy because the solution sorts in place
            checksum += sol.maxStability(t.n, edgesCopy, t.k);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Time (microseconds): " << elapsed_us << "\n";

    return 0;
}