#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <utility>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <chrono>

using namespace std;

// Time:  O((|E| + |V|) * log|V|) = O(|E| * log|V|)
// Space: O(|E| + |V|)

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        vector<vector<pair<int, int>>> adj(N);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        using PLL = pair<long long, int>;
        priority_queue<PLL, vector<PLL>, greater<PLL>> min_heap;
        const long long INF = numeric_limits<long long>::max() / 4;

        vector<long long> best(N, INF);
        vector<unordered_map<int, int>> count(N);

        best[0] = 0;
        min_heap.emplace(0LL, 0);

        long long result = 0;
        while (!min_heap.empty()) {
            auto [curr_total, u] = min_heap.top();
            min_heap.pop();
            if (curr_total != best[u]) {
                continue;
            }
            if (curr_total > M) {
                continue;
            }
            result += 1;
            for (const auto& p : adj[u]) {
                int v = p.first;
                int w = p.second;
                long long remain = M - curr_total;
                int take = static_cast<int>(min<long long>(w, max<long long>(0, remain)));
                count[u][v] = take;
                long long next_total = curr_total + w + 1;
                if (next_total <= M && next_total < best[v]) {
                    best[v] = next_total;
                    min_heap.emplace(next_total, v);
                }
            }
        }

        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            long long a = 0, b = 0;
            auto it = count[u].find(v);
            if (it != count[u].end()) a = it->second;
            auto jt = count[v].find(u);
            if (jt != count[v].end()) b = jt->second;
            result += min<long long>(w, a + b);
        }

        return static_cast<int>(result);
    }
};

struct TestCase {
    vector<vector<int>> edges;
    int M;
    int N;
};

int main() {
    // Define 10 diverse test cases
    vector<TestCase> tests;
    {
        // 1) Simple single edge, limited M
        vector<vector<int>> edges1 = {{0, 1, 10}};
        tests.push_back({edges1, 6, 2});
    }
    {
        // 2) Triangle graph with varying weights
        vector<vector<int>> edges2 = {{0, 1, 4}, {1, 2, 6}, {0, 2, 8}};
        tests.push_back({edges2, 10, 3});
    }
    {
        // 3) Linear chain
        vector<vector<int>> edges3;
        for (int i = 0; i < 4; ++i) edges3.push_back({i, i + 1, 1});
        tests.push_back({edges3, 3, 5});
    }
    {
        // 4) Star graph centered at 0
        vector<vector<int>> edges4 = {
            {0, 1, 2}, {0, 2, 3}, {0, 3, 1}, {0, 4, 5}, {0, 5, 7}, {0, 6, 0}
        };
        tests.push_back({edges4, 5, 7});
    }
    {
        // 5) Zero moves, only node 0 reachable
        vector<vector<int>> edges5 = {{0, 1, 3}, {1, 2, 3}};
        tests.push_back({edges5, 0, 3});
    }
    {
        // 6) Dense graph with 10 nodes
        vector<vector<int>> edges6;
        int N6 = 10;
        for (int i = 0; i < N6; ++i) {
            for (int j = i + 1; j < N6; ++j) {
                int w = ((i * 7 + j * 11) % 5) + 1; // weights in [1,5]
                edges6.push_back({i, j, w});
            }
        }
        tests.push_back({edges6, 20, N6});
    }
    {
        // 7) Disjoint components
        vector<vector<int>> edges7 = {
            {0, 1, 2}, {1, 2, 2}, // component with node 0
            {4, 5, 1}, {5, 6, 1}, {6, 7, 1} // separate component
        };
        tests.push_back({edges7, 3, 8});
    }
    {
        // 8) Very large weights and M to test 64-bit handling
        vector<vector<int>> edges8 = {
            {0, 1, 1000000000}, {1, 2, 1000000000}
        };
        tests.push_back({edges8, 1000000000, 3});
    }
    {
        // 9) Single node, no edges
        vector<vector<int>> edges9;
        tests.push_back({edges9, 10, 1});
    }
    {
        // 10) Cycle with zero-weight edges
        vector<vector<int>> edges10 = {
            {0, 1, 0}, {1, 2, 0}, {2, 3, 0}, {3, 0, 0}, {0, 2, 0}
        };
        tests.push_back({edges10, 2, 4});
    }

    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        Solution sol;
        for (const auto& t : tests) {
            // Make a local copy because the function takes non-const reference
            auto edges = t.edges;
            int res = sol.reachableNodes(edges, t.M, t.N);
            checksum += res;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}