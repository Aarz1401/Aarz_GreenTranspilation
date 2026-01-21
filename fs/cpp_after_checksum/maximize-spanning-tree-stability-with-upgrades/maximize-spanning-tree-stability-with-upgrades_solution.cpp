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
