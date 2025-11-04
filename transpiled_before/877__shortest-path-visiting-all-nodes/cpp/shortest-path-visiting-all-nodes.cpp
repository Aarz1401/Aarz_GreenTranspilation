#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <algorithm>
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