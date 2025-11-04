#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int R = ring.size();
        unordered_map<char, vector<int>> lookup;
        lookup.reserve(64);
        for (int i = 0; i < R; ++i) {
            lookup[ring[i]].push_back(i);
        }

        vector<vector<int>> dp(2, vector<int>(R, 0));
        vector<int> prev(1, 0);

        for (int i = 1; i <= (int)key.size(); ++i) {
            int cur = i & 1;
            int pre = (i - 1) & 1;
            for (int j = 0; j < R; ++j) dp[cur][j] = INT_MAX / 4;

            const auto& positions = lookup[key[i - 1]];
            for (int j : positions) {
                for (int k : prev) {
                    int cw = (j - k + R) % R;
                    int ccw = (k - j + R) % R;
                    int dist = min(cw, ccw);
                    dp[cur][j] = min(dp[cur][j], dp[pre][k] + dist);
                }
            }
            prev = positions;
        }

        int minSteps = INT_MAX;
        int idx = key.size() & 1;
        for (int v : dp[idx]) minSteps = min(minSteps, v);
        return minSteps + (int)key.size();
    }
};