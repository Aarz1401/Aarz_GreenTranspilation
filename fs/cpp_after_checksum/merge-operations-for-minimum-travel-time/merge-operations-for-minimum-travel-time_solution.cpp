#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <chrono>
#include <chrono>
using namespace std;

class Solution {
public:
    int minTravelTime(int l, int n, int k, vector<int>& position, vector<int>& time) {
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix[i + 1] = prefix[i] + time[i];
        }

        vector<unordered_map<long long, long long>> dp(n), new_dp(n);
        dp[0][time[0]] = 0;

        for (int cnt = 2; cnt <= n - k; ++cnt) {
            for (int i = 0; i < n; ++i) new_dp[i].clear();
            for (int i = cnt - 1; i <= (cnt - 1) + k && i < n; ++i) {
                for (int j = cnt - 2; j <= i - 1; ++j) {
                    if (j < 0 || dp[j].empty()) continue;
                    long long tnew = prefix[i + 1] - prefix[j + 1];
                    long long dist = static_cast<long long>(position[i]) - static_cast<long long>(position[j]);
                    for (const auto& kv : dp[j]) {
                        long long t = kv.first;
                        long long c = kv.second;
                        long long val = dist * t + c;
                        auto it = new_dp[i].find(tnew);
                        if (it == new_dp[i].end() || val < it->second) {
                            new_dp[i][tnew] = val;
                        }
                    }
                }
            }
            dp.swap(new_dp);
        }

        long long ans = LLONG_MAX;
        for (const auto& kv : dp[n - 1]) {
            ans = min(ans, kv.second);
        }
        return static_cast<int>(ans);
    }
};

struct Test {
    int l;
    int n;
    int k;
    vector<int> position;
    vector<int> time;
};
