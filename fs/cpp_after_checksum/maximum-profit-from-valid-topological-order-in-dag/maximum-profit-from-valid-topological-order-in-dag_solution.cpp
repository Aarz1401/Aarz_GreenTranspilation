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

using namespace std;
using namespace std::chrono;

class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> adj(n, 0);
        for (const auto& e : edges) {
            int i = e[0], j = e[1];
            adj[j] |= (1 << i);
        }
        int total = 1 << n;
        const long long NEG = LLONG_MIN / 4;
        vector<long long> dp(total, NEG);
        dp[0] = 0;
        for (int mask = 0; mask < total; ++mask) {
            if (dp[mask] == NEG) continue;
            int l = __builtin_popcount((unsigned)mask) + 1;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) continue;
                if ((mask & adj[i]) == adj[i]) {
                    int nmask = mask | (1 << i);
                    dp[nmask] = max(dp[nmask], dp[mask] + 1LL * l * score[i]);
                }
            }
        }
        return static_cast<int>(dp[total - 1]);
    }
};

struct TestCase {
    int n;
    vector<vector<int>> edges;
    vector<int> score;
};
