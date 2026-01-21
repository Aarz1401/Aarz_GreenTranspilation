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
#include <chrono>
#include <cstdint>
#include <utility>
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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<vector<vector<int>>, vector<vector<int>>>> tests;
    tests.reserve(10);

    // Test 1: n=1 (single node)
    vector<vector<int>> edges1_1 = {};
    vector<vector<int>> edges2_1 = {};
    tests.push_back({edges1_1, edges2_1});

    // Test 2: n=2
    vector<vector<int>> edges1_2 = {{0,1}};
    vector<vector<int>> edges2_2 = {{0,1}};
    tests.push_back({edges1_2, edges2_2});

    // Test 3: n=3 (chain vs star)
    vector<vector<int>> edges1_3 = {{0,1},{1,2}};
    vector<vector<int>> edges2_3 = {{0,1},{0,2}};
    tests.push_back({edges1_3, edges2_3});

    // Test 4: n=4 (chain vs star)
    vector<vector<int>> edges1_4 = {{0,1},{1,2},{2,3}};
    vector<vector<int>> edges2_4 = {{0,1},{0,2},{0,3}};
    tests.push_back({edges1_4, edges2_4});

    // Test 5: n=5 (star centered at 2 vs chain)
    vector<vector<int>> edges1_5 = {{2,0},{2,1},{2,3},{2,4}};
    vector<vector<int>> edges2_5 = {{0,1},{1,2},{2,3},{3,4}};
    tests.push_back({edges1_5, edges2_5});

    // Test 6: n=6 (two different trees)
    vector<vector<int>> edges1_6 = {{0,1},{1,2},{1,3},{3,4},{4,5}};
    vector<vector<int>> edges2_6 = {{0,2},{2,1},{1,3},{3,4},{4,5}};
    tests.push_back({edges1_6, edges2_6});

    // Test 7: n=7 (binary-like vs chain)
    vector<vector<int>> edges1_7 = {{0,1},{0,2},{1,3},{1,4},{2,5},{5,6}};
    vector<vector<int>> edges2_7 = {{0,1},{1,2},{2,3},{3,4},{4,5},{5,6}};
    tests.push_back({edges1_7, edges2_7});

    // Test 8: n=8 (skewed vs star centered at 7)
    vector<vector<int>> edges1_8 = {{0,1},{0,2},{2,3},{2,4},{4,5},{5,6},{6,7}};
    vector<vector<int>> edges2_8 = {{7,0},{7,1},{7,2},{7,3},{7,4},{7,5},{7,6}};
    tests.push_back({edges1_8, edges2_8});

    // Test 9: n=9 (random vs reversed chain-like)
    vector<vector<int>> edges1_9 = {{0,1},{1,2},{2,3},{3,4},{1,5},{5,6},{6,7},{7,8}};
    vector<vector<int>> edges2_9 = {{0,8},{8,7},{7,6},{6,5},{5,4},{4,3},{3,2},{2,1}};
    tests.push_back({edges1_9, edges2_9});

    // Test 10: n=10 (balanced-ish vs chain)
    vector<vector<int>> edges1_10 = {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{5,7},{5,8},{6,9}};
    vector<vector<int>> edges2_10 = {{0,9},{9,8},{8,7},{7,6},{6,5},{5,4},{4,3},{3,2},{2,1}};
    tests.push_back({edges1_10, edges2_10});

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tt : tests) {
            vector<vector<int>> e1 = tt.first;
            vector<vector<int>> e2 = tt.second;
            auto res = sol.maxTargetNodes(e1, e2);
            for (int v : res) {
                checksum += (v ^ iter);
            }
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed (ns): " << elapsed_ns << "\n";
    return 0;
}