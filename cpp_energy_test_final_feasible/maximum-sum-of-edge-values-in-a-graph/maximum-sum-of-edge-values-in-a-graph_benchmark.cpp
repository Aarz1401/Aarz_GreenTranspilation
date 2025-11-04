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
#include <utility>

using namespace std;

class Solution {
public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(n, false);
        auto bfs = [&](int start) {
            vector<int> comp;
            queue<int> q;
            visited[start] = true;
            q.push(start);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                comp.push_back(u);
                for (int v : adj[u]) {
                    if (visited[v]) continue;
                    visited[v] = true;
                    q.push(v);
                }
            }
            return comp;
        };

        auto f = [&](long long l, long long r, bool is_cycle) -> long long {
            long long a = r, b = r;
            long long result = 0;
            for (long long c = r - 1; c >= l; --c) {
                result += a * c;
                long long na = b, nb = c;
                a = na, b = nb;
            }
            if (is_cycle) {
                result += a * b;
            }
            return result;
        };

        vector<int> cycles, chains;
        for (int u = 0; u < n; ++u) {
            if (visited[u]) continue;
            vector<int> comp = bfs(u);
            bool is_cycle = true;
            for (int x : comp) {
                if (adj[x].size() != 2) { is_cycle = false; break; }
            }
            if (is_cycle) {
                cycles.push_back((int)comp.size());
            } else {
                chains.push_back((int)comp.size());
            }
        }

        long long result = 0;
        int cur = n;
        for (int l : cycles) {
            result += f(cur - l + 1, cur, true);
            cur -= l;
        }

        size_t max_len = 0;
        for (int l : chains) max_len = max(max_len, (size_t)l);
        vector<int> cnt(max_len + 1, 0);
        for (int l : chains) cnt[l]++;

        for (int l = (int)cnt.size() - 1; l >= 0; --l) {
            for (int k = 0; k < cnt[l]; ++k) {
                result += f(cur - l + 1, cur, false);
                cur -= l;
            }
        }
        return result;
    }
};

int main() {
    // Define 10 diverse test inputs
    vector<pair<int, vector<vector<int>>>> tests;
    tests.reserve(10);

    // 1) Empty graph
    tests.push_back({0, {}});

    // 2) Single node, no edges
    tests.push_back({1, {}});

    // 3) Single node with a self-loop (degree 2, treated as a cycle of length 1)
    tests.push_back({1, {{0, 0}}});

    // 4) Two nodes, one edge (simple chain)
    tests.push_back({2, {{0, 1}}});

    // 5) Triangle cycle (3-cycle)
    tests.push_back({3, {{0, 1}, {1, 2}, {2, 0}}});

    // 6) Mixed: 3-cycle + path of length 3 + isolated node
    // Nodes: 0-1-2-0 (cycle), 3-4-5 (path), 6 isolated
    tests.push_back({7, {{0,1}, {1,2}, {2,0}, {3,4}, {4,5}}});

    // 7) Star graph with 6 nodes (center 0 connected to 1..5)
    tests.push_back({6, {{0,1}, {0,2}, {0,3}, {0,4}, {0,5}}});

    // 8) Complete graph K5
    {
        int n = 5;
        vector<vector<int>> edges;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                edges.push_back({i, j});
            }
        }
        tests.push_back({n, std::move(edges)});
    }

    // 9) Mixed: 4-cycle with a tail + a 3-path + two isolated nodes
    // 0-1-2-3-0 (cycle), tail 1-4, path 5-6-7, isolated 8 and 9
    tests.push_back({10, {{0,1}, {1,2}, {2,3}, {3,0}, {1,4}, {5,6}, {6,7}}});

    // 10) Mixed: three disjoint edges, a 4-cycle, and two isolated nodes
    // Edges: (0-1), (2-3), (4-5), 8-9-10-11-8 cycle; 6 and 7 isolated
    tests.push_back({12, {{0,1}, {2,3}, {4,5}, {8,9}, {9,10}, {10,11}, {11,8}}});

    Solution sol;
    long long accumulator = 0;

    const int iterations = 1000;
    auto start = std::chrono::high_resolution_clock::now();

    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& test : tests) {
            accumulator += sol.maxScore(test.first, test.second);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // Print result to avoid compiler optimizing away computations
    std::cout << "Accumulated result: " << accumulator << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    std::cout << "Elapsed time (ms): " << (elapsed_ns / 1e6) << "\n";
    return 0;
}