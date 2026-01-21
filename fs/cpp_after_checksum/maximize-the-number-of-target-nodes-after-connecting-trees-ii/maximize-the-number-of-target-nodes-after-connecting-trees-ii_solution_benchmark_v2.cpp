#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Time:  O(n + m)
// Space: O(n + m)

// bfs
class Solution {
public:
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        auto find_adj = [&](const vector<vector<int>>& edges) {
            int n = static_cast<int>(edges.size()) + 1;
            vector<vector<int>> adj(n);
            for (const auto& e : edges) {
                int u = e[0], v = e[1];
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
            return adj;
        };

        auto bfs = [&](const vector<vector<int>>& adj) {
            int n = static_cast<int>(adj.size());
            vector<int> lookup(n, -1);
            int parity = 0;
            vector<int> q = {0};
            lookup[0] = parity;
            while (!q.empty()) {
                vector<int> new_q;
                for (int u : q) {
                    for (int v : adj[u]) {
                        if (lookup[v] != -1) {
                            continue;
                        }
                        lookup[v] = parity ^ 1;
                        new_q.push_back(v);
                    }
                }
                q.swap(new_q);
                parity ^= 1;
            }
            int cnt = 0;
            for (int x : lookup) {
                if (x != -1) cnt += x;
            }
            vector<int> res(n);
            for (int u = 0; u < n; ++u) {
                res[u] = lookup[u] ? cnt : (n - cnt);
            }
            return res;
        };

        vector<vector<int>> adj2 = find_adj(edges2);
        vector<int> b2 = bfs(adj2);
        int mx = *max_element(b2.begin(), b2.end());
        vector<vector<int>> adj1 = find_adj(edges1);
        vector<int> b1 = bfs(adj1);
        for (int& x : b1) {
            x += mx;
        }
        return b1;
    }
};

struct Test {
    vector<vector<int>> e1;
    vector<vector<int>> e2;
};

int main() {
    vector<Test> tests = {
        // 1
        { { {0,1} },
          { {0,1} } },
        // 2
        { { {0,1},{0,2},{0,3},{0,4} },
          { {0,1},{1,2},{2,3} } },
        // 3
        { { {0,1},{1,2},{2,3},{3,4},{4,5} },
          { {1,0},{1,2},{1,3},{1,4},{1,5} } },
        // 4
        { { {0,1},{0,2},{1,3},{1,4},{2,5},{2,6} },
          { {0,1},{1,2},{2,3},{3,4} } },
        // 5
        { { {0,2},{2,3},{3,4},{4,5},{5,6},{2,1},{6,7} },
          { {3,0},{3,1},{3,2},{3,4},{3,5},{3,6},{3,7} } },
        // 6
        { { {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9} },
          { {0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{3,8} } },
        // 7
        { { {0,1},{1,2} },
          { {0,1},{0,2},{0,3},{0,4},{0,5},{0,6} } },
        // 8
        { { {5,0},{5,1},{5,2},{5,3},{5,4},{5,6},{5,7},{5,8},{5,9},{5,10} },
          { {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10} } },
        // 9
        { { {0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{5,7},{5,8},{6,9},{4,10},{10,11} },
          { {0,1},{1,2},{2,3},{3,4},{4,5},{2,6},{6,7},{6,8},{4,9},{9,10},{10,11},{11,12} } },
        // 10
        { { {0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{3,8},{4,9},{4,10},{5,11},{5,12},{6,13},{6,14} },
          { {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14} } }
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<vector<int>> e1 = t.e1;
            vector<vector<int>> e2 = t.e2;
            vector<int> res = sol.maxTargetNodes(e1, e2);
            for (int x : res) checksum += x;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}