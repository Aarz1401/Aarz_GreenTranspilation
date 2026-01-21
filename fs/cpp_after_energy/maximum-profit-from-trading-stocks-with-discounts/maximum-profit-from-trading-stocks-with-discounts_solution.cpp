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
#include <functional>
#include <chrono>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}
using namespace std::chrono;

class Solution {
public:
    int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
        vector<vector<int>> adj(n);
        for (const auto& e : hierarchy) {
            int u = e[0] - 1;
            int v = e[1] - 1;
            adj[u].push_back(v);
        }
        function<vector<unordered_map<int, int>>(int)> dfs = [&](int u) -> vector<unordered_map<int, int>> {
            vector<unordered_map<int, int>> dp(2);
            dp[0][0] = 0;
            dp[1][0] = 0;
            for (int v : adj[u]) {
                auto child = dfs(v);
                vector<unordered_map<int, int>> next(2);
                const int iterations = 1000;
                for (int iter = 0; iter < iterations; ++iter) {
                    for (const auto& p1 : dp[i]) {
                        int j1 = p1.first, v1 = p1.second;
                        for (const auto& p2 : child[i]) {
                            int j2 = p2.first, v2 = p2.second;
                            int sum = j1 + j2;
                            if (sum <= budget) {
                                int val = v1 + v2;
                                auto it = next[i].find(sum);
                                if (it == next[i].end()) next[i][sum] = val;
                                else if (it->second < val) it->second = val;
                            }
                        }
                    }
                }
                dp.swap(next);
            }
            vector<unordered_map<int, int>> result(2);
            for (int i = 0; i < 2; ++i) {
                for (const auto& p : dp[0]) {
                    int j = p.first, v = p.second;
                    auto it = result[i].find(j);
                    if (it == result[i].end() || it->second < v) result[i][j] = v;
                }
                int cost = present[u] >> i;
                if (cost <= budget) {
                    int profit = future[u] - cost;
                    for (const auto& p : dp[1]) {
                        int j = p.first, v = p.second;
                        int total = j + cost;
                        if (total <= budget) {
                            int val = v + profit;
                            auto it = result[i].find(total);
                            if (it == result[i].end() || it->second < val) result[i][total] = val;
                        }
                    }
                }
            }
            return result;
        };

        auto res = dfs(0);
        int ans = 0;
        for (const auto& p : res[0]) {
            ans = max(ans, p.second);
        }
        return ans;
    }
};

struct TestCase {
    int n;
    vector<int> present;
    vector<int> future;
    vector<vector<int>> hierarchy;
    int budget;
};
