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
#include <numeric>
#include <chrono>
#include <cstdint>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        using int64 = long long;
        const int64 INF = LLONG_MAX / 4;

        auto gcdll = [&](int64 a, int64 b) {
            while (b) {
                int64 t = a % b;
                a = b;
                b = t;
            }
            return a;
        };

        auto lcm_saturate = [&](int64 a, int64 b) {
            if (a == 0 || b == 0) return 0LL;
            int64 g = gcdll(a, b);
            int64 t = a / g;
            if (t > INF / b) return INF;
            return t * b;
        };

        int n = nums.size();
        int m = target.size();
        int total = 1 << m;

        vector<int64> lcms(total, 1);
        for (int mask = 0; mask < total; ++mask) {
            int64 l = 1;
            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    l = lcm_saturate(l, static_cast<int64>(target[i]));
                    if (l >= INF) { l = INF; break; }
                }
            }
            lcms[mask] = l;
        }

        vector<int64> dp(total, INF);
        dp[0] = 0;

        for (int x : nums) {
            for (int mask = total - 1; mask >= 0; --mask) {
                if (dp[mask] == INF) continue;
                int new_mask = (total - 1) ^ mask;
                int submask = new_mask;
                while (submask) {
                    int64 l = lcms[submask];
                    int64 rem = l == 0 ? 0 : (static_cast<int64>(x) % l);
                    int64 inc = (rem == 0) ? 0 : (l - rem);
                    dp[mask | submask] = min(dp[mask | submask], dp[mask] + inc);
                    submask = (submask - 1) & new_mask;
                }
            }
        }

        return static_cast<int>(dp[total - 1]);
    }
};
