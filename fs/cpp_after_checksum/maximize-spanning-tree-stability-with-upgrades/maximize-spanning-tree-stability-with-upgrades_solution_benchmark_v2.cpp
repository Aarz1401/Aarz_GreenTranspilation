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

volatile int sink = 0;

int main() {
    vector<TestCase> tests = {
        // 1) Simple optional edge, k=0
        {2, {{0,1,5,0}}, 0},
        // 2) One mandatory, others optional, k=1
        {3, {{0,1,7,1},{1,2,6,0},{0,2,4,0}}, 1},
        // 3) Mandatory cycle -> -1
        {3, {{0,1,5,1},{1,2,4,1},{0,2,3,1}}, 0},
        // 4) Disconnected after all edges -> -1
        {4, {{0,1,10,1},{2,3,9,0}}, 0},
        // 5) k > n-1, result from final 2*s
        {3, {{0,1,3,0},{1,2,2,0}}, 5},
        // 6) Pure optional spanning tree, k=0, result is last s
        {4, {{0,1,10,0},{1,2,9,0},{2,3,8,0},{0,2,7,0}}, 0},
        // 7) Mandatory high s, final 2*s smaller with k=1
        {4, {{0,1,50,1},{1,2,40,0},{2,3,20,0}}, 1},
        // 8) Zero-weight edges
        {3, {{0,1,0,1},{1,2,0,0}}, 0},
        // 9) Equal weights, large k
        {5, {{0,1,1,0},{1,2,1,0},{2,3,1,0},{3,4,1,0}}, 10},
        // 10) Mixed with multiple components and k=2
        {6, {{0,1,9,1},{2,3,8,1},{1,2,7,0},{3,4,6,0},{4,5,5,0},{0,2,4,0},{5,0,3,0}}, 2}
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            vector<vector<int>> edgesCopy = tc.edges;
            int res = sol.maxStability(tc.n, edgesCopy, tc.k);
            checksum += res;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}