#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
using namespace std;
using namespace std::chrono;

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

int main() {
    // Define 10 diverse test inputs (pairs of trees as edge lists)
    vector<vector<vector<int>>> edges1_list;
    vector<vector<vector<int>>> edges2_list;
    edges1_list.reserve(10);
    edges2_list.reserve(10);

    // Test 1: Single node trees
    edges1_list.push_back({}); // n1=1
    edges2_list.push_back({}); // n2=1

    // Test 2: Two-node trees
    edges1_list.push_back({{0,1}});
    edges2_list.push_back({{0,1}});

    // Test 3: Chain vs Star (4 nodes)
    edges1_list.push_back({{0,1},{1,2},{2,3}});
    edges2_list.push_back({{0,1},{0,2},{0,3}});

    // Test 4: Balanced binary tree (7 nodes) vs Chain (7 nodes)
    edges1_list.push_back({
        {0,1},{0,2},{1,3},{1,4},{2,5},{2,6}
    });
    edges2_list.push_back({
        {0,1},{1,2},{2,3},{3,4},{4,5},{5,6}
    });

    // Test 5: Long Chain (10 nodes) vs Star (10 nodes)
    edges1_list.push_back({
        {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},{8,9}
    });
    edges2_list.push_back({
        {0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},{0,9}
    });

    // Test 6: Star (8 nodes) vs balanced-ish (8 nodes)
    edges1_list.push_back({
        {0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7}
    });
    edges2_list.push_back({
        {0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{6,7}
    });

    // Test 7: Random tree (12 nodes) vs small chain (5 nodes)
    edges1_list.push_back({
        {0,1},{1,2},{1,3},{3,4},{2,5},{5,6},{0,7},{7,8},{8,9},{9,10},{10,11}
    });
    edges2_list.push_back({
        {0,1},{1,2},{2,3},{3,4}
    });

    // Test 8: Two different random trees (6 nodes)
    edges1_list.push_back({
        {0,1},{1,2},{1,3},{3,4},{4,5}
    });
    edges2_list.push_back({
        {0,2},{2,3},{3,1},{1,4},{4,5}
    });

    // Test 9: Balanced (15 nodes) vs random (15 nodes)
    edges1_list.push_back({
        {0,1},{0,2},{1,3},{1,4},{2,5},{2,6},
        {3,7},{3,8},{4,9},{4,10},{5,11},{5,12},{6,13},{6,14}
    });
    edges2_list.push_back({
        {0,1},{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},
        {3,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14}
    });

    // Test 10: Irregular (16 nodes) vs branching (16 nodes)
    edges1_list.push_back({
        {0,1},{1,2},{2,3},{3,4},{1,5},{5,6},{6,7},
        {0,8},{8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15}
    });
    edges2_list.push_back({
        {0,1},{0,2},{0,3},{3,4},{3,5},{5,6},{5,7},
        {2,8},{2,9},{9,10},{10,11},{10,12},{1,13},{13,14},{14,15}
    });

    Solution sol;

    // Run benchmark
    const int iterations = 1000;
    volatile unsigned long long checksum = 0;

    auto start = high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < edges1_list.size(); ++i) {
            vector<int> res = sol.maxTargetNodes(edges1_list[i], edges2_list[i]);
            for (int x : res) {
                checksum += static_cast<unsigned long long>(x);
            }
        }
    }
    auto end = high_resolution_clock::now();
    auto dur_ms = duration_cast<milliseconds>(end - start).count();

    // Print result and timing
    cout << "Checksum: " << static_cast<unsigned long long>(checksum) << "\n";
    cout << "Time (ms): " << dur_ms << "\n";
    return 0;
}