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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int magicalSum(int m, int k, vector<int>& nums) {
        const int MOD = 1000000007;

        // Precompute factorials, modular inverses, and inverse factorials up to m
        vector<long long> fact(m + 1, 1), inv(m + 1, 1), inv_fact(m + 1, 1);
        if (m >= 1) {
            inv[1] = 1;
            for (int i = 2; i <= m; ++i) {
                inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD; // linear-time modular inverses
            }
            for (int i = 1; i <= m; ++i) {
                fact[i] = fact[i - 1] * i % MOD;
                inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD;
            }
        }

        // dp[c][b][l]: sum of carry c with b set bits with remaining size l
        vector<vector<vector<long long>>> dp(m + 1, vector<vector<long long>>(k + 1, vector<long long>(m + 1, 0)));
        dp[0][0][m] = 1;

        for (int x : nums) {
            long long xm = ((x % MOD) + MOD) % MOD;
            vector<vector<vector<long long>>> new_dp(m + 1, vector<vector<long long>>(k + 1, vector<long long>(m + 1, 0)));
            for (int c = 0; c <= m; ++c) {
                for (int b = 0; b <= k; ++b) {
                    for (int l = 0; l <= m; ++l) {
                        long long cur = dp[c][b][l];
                        if (!cur) continue;
                        long long base = 1;
                        for (int cnt = 0; cnt <= l; ++cnt) {
                            int nc = (c + cnt) >> 1;
                            int nb = b + ((c + cnt) & 1);
                            int nl = l - cnt;
                            if (nb <= k) {
                                long long add = cur;
                                add = (add * base) % MOD;
                                add = (add * inv_fact[cnt]) % MOD;
                                new_dp[nc][nb][nl] += add;
                                if (new_dp[nc][nb][nl] >= MOD) new_dp[nc][nb][nl] -= MOD;
                            }
                            base = (base * xm) % MOD;
                        }
                    }
                }
            }
            dp.swap(new_dp);
        }

        long long ans = 0;
        for (int c = 0; c <= m; ++c) {
            int pc = __builtin_popcount((unsigned int)c);
            int rem = k - pc;
            if (rem >= 0 && rem <= k) {
                ans += dp[c][rem][0];
                if (ans >= MOD) ans -= MOD;
            }
        }
        ans = ans * fact[m] % MOD;
        return static_cast<int>(ans);
    }
};

struct TestCase {
    int m;
    int k;
    vector<int> nums;
};
