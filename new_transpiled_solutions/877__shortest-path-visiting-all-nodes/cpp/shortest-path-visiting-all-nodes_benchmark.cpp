#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>
#include <chrono>
using namespace std;

// Time:  O(n * 2^n)
// Space: O(n * 2^n)

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = static_cast<int>(graph.size());
        if (n <= 1) return 0;

        const int FULL = (1 << n) - 1;
        const int INF = numeric_limits<int>::max() / 4;
        vector<vector<int>> dp(1 << n, vector<int>(n, INF));
        queue<pair<int, int>> q;

        for (int i = 0; i < n; ++i) {
            dp[1 << i][i] = 0;
            q.emplace(1 << i, i);
        }

        while (!q.empty()) {
            auto [state, node] = q.front();
            q.pop();
            int steps = dp[state][node];
            for (int nei : graph[node]) {
                int new_state = state | (1 << nei);
                if (dp[new_state][nei] == INF) {
                    dp[new_state][nei] = steps + 1;
                    q.emplace(new_state, nei);
                }
            }
        }

        int result = INF;
        for (int i = 0; i < n; ++i) {
            result = min(result, dp[FULL][i]);
        }
        return result;
    }
};

int main() {
    // Define 10 diverse test graphs
    vector<vector<vector<int>>> tests = {
        {}, // 0: empty graph
        {{}}, // 1: single node
        {{1}, {0}}, // 2: two nodes connected
        {{1}, {0,2}, {1}}, // 3: line of 3
        {{1,2}, {0,2}, {0,1}}, // 4: triangle
        {{1,3}, {0,2}, {1,3}, {0,2}}, // 5: 4-cycle
        {{1,2,3,4}, {0}, {0}, {0}, {0}}, // 6: star with 5 nodes, center 0
        {{1}, {0,2}, {1,3}, {2,4}, {3,5}, {4,6}, {5,7}, {6}}, // 7: line of 8
        { // 8: complete graph K6
          {1,2,3,4,5},
          {0,2,3,4,5},
          {0,1,3,4,5},
          {0,1,2,4,5},
          {0,1,2,3,5},
          {0,1,2,3,4}
        },
        { // 9: 12-node connected mixed graph
          {1,5},
          {0,2,6},
          {1,3,7},
          {2,4,8},
          {3,5,9},
          {4,0,10},
          {1,7,11},
          {2,6,8,9},
          {3,7,9,10},
          {4,7,8,10,11},
          {5,8,9,11},
          {6,9,10}
        }
    };

    Solution sol;
    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& g : tests) {
            checksum += sol.shortestPathLength(g);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}