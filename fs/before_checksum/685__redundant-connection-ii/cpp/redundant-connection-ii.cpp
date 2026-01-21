#include <vector>
#include <algorithm>

using namespace std;

// Time:  O(nlog*n) ~= O(n), n is the length of the positions
// Space: O(n)

class UnionFind {
public:
    explicit UnionFind(int n) : parent(n) {
        for (int i = 0; i < n; ++i) parent[i] = i;
    }

    int find_set(int x) {
        if (parent[x] != x) {
            parent[x] = find_set(parent[x]);  // path compression.
        }
        return parent[x];
    }

    bool union_set(int x, int y) {
        int x_root = find_set(x);
        int y_root = find_set(y);
        if (x_root == y_root) {
            return false;
        }
        parent[min(x_root, y_root)] = max(x_root, y_root);
        return true;
    }

private:
    vector<int> parent;
};

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        vector<int> cand1, cand2;
        int n = static_cast<int>(edges.size());
        vector<int> parent(n + 1, 0);

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            if (parent[v] == 0) {
                parent[v] = u;
            } else {
                cand1 = {parent[v], v};
                cand2 = edge;
            }
        }

        UnionFind union_find(n + 1);
        for (const auto& edge : edges) {
            if (!cand2.empty() && edge[0] == cand2[0] && edge[1] == cand2[1]) {
                continue;
            }
            if (!union_find.union_set(edge[0], edge[1])) {
                return !cand2.empty() ? cand1 : edge;
            }
        }
        return cand2;
    }
};