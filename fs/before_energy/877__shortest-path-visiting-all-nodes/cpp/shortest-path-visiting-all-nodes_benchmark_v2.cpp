#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    vector<vector<vector<int>>> tests = {
        { {} },                                         // n=1
        { {1}, {0} },                                   // n=2
        { {1}, {0,2}, {1} },                            // n=3 path
        { {1,3}, {0,2}, {1,3}, {0,2} },                 // n=4 cycle
        { {1,2,3,4}, {0}, {0}, {0}, {0} },              // n=5 star
        { {1,2,3,4,5}, {0,2,3,4,5}, {0,1,3,4,5},        // n=6 complete
          {0,1,2,4,5}, {0,1,2,3,5}, {0,1,2,3,4} },
        { {1,2}, {0,2,4}, {0,1,3,6}, {2,4},             // n=7 mixed
          {1,3,5}, {4,6}, {5,2} },
        { {1,4}, {0,2,5}, {1,3,6}, {2,7},               // n=8 grid 2x4
          {0,5}, {1,4,6}, {2,5,7}, {3,6} },
        { {1,3}, {0,2,4}, {1,5},                        // n=9 grid 3x3
          {0,4,6}, {1,3,5,7}, {2,4,8},
          {3,7}, {4,6,8}, {5,7} },
        { {1,4}, {0,2}, {1,3}, {2,4},                   // n=10 two 5-cycles + bridge
          {3,0,5}, {6,9,4}, {5,7}, {6,8}, {7,9}, {8,5} }
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            int r = sol.shortestPathLength(tests[i]);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}