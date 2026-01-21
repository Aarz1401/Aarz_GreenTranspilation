#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    vector<Test> tests = {
        {10, 2, 0, {0, 5}, {2, 3}},
        {20, 3, 1, {0, 4, 9}, {1, 2, 3}},
        {30, 5, 2, {0, 2, 5, 9, 14}, {1, 3, 2, 4, 1}},
        {40, 6, 3, {0, 1, 3, 6, 10, 15}, {2, 2, 1, 3, 2, 1}},
        {50, 7, 5, {0, 1, 2, 3, 4, 5, 6}, {1, 1, 1, 1, 1, 1, 1}},
        {60, 8, 6, {0, 2, 3, 7, 11, 12, 13, 20}, {2, 1, 3, 1, 2, 3, 1, 2}},
        {70, 9, 7, {0, 3, 5, 8, 12, 13, 17, 18, 25}, {3, 2, 4, 1, 2, 5, 1, 3, 2}},
        {80, 10, 8, {0, 5, 6, 10, 11, 16, 20, 23, 27, 30}, {2, 2, 3, 4, 1, 3, 2, 4, 1, 2}},
        {90, 12, 10, {0, 1, 3, 6, 10, 15, 21, 22, 24, 27, 31, 36}, {1, 2, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1}},
        {100, 15, 13, {0, 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, 56, 60, 65, 71}, {1, 3, 2, 4, 1, 2, 3, 1, 2, 3, 4, 1, 2, 3, 1}}
    };

    Solution sol;

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            int res = sol.minTravelTime(t.l, t.n, t.k, const_cast<vector<int>&>(t.position), const_cast<vector<int>&>(t.time));
            DoNotOptimize(res); 
            // checksum += res;
        }
        //sink = checksum;
    }

    return 0;
}