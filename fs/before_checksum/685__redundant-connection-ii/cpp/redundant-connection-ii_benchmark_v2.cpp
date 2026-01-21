#include <iostream>
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

int main() {
    // 10 diverse valid test inputs
    vector<vector<vector<int>>> tests = {
        {{1,2},{1,3},{2,3}},                               // two-parent, no cycle
        {{1,2},{2,3},{3,4},{4,1},{1,5}},                   // cycle, no two-parent
        {{2,1},{3,1},{4,2},{1,4}},                         // both: cycle + two-parent
        {{1,2},{1,3},{2,4},{3,4},{4,5}},                   // two-parent, no cycle
        {{1,2},{1,3},{2,4},{3,5},{5,6},{6,1}},             // cycle, no two-parent
        {{1,2},{2,1}},                                     // small cycle
        {{1,2},{1,3},{2,4},{2,5},{3,5},{3,6},{6,7}},       // two-parent, no cycle
        {{4,2},{1,2},{2,3},{3,4},{2,5}},                   // both: cycle + two-parent
        {{1,2},{1,3},{2,4},{3,5},{4,6},{6,1}},             // cycle, no two-parent
        {{1,2},{2,3},{3,4},{1,3}}                          // two-parent, no cycle
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            vector<int> r = sol.findRedundantDirectedConnection(t);
            checksum += r[0] * 131 + r[1];
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}