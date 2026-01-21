#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <cstdint>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        const long long M = 1000000007LL;
        const int W = 3;
        int n = static_cast<int>(s.size());
        vector<long long> dp(W, 0);
        dp[0] = 1;
        if (s[0] == '*') {
            dp[1] = 9;
        } else if (s[0] != '0') {
            dp[1] = dp[0];
        } else {
            dp[1] = 0;
        }
        for (int i = 1; i < n; ++i) {
            int cur = (i + 1) % W;
            int prev = i % W;
            int prevprev = (i - 1) % W;
            if (s[i] == '*') {
                dp[cur] = (9LL * dp[prev]) % M;
                if (s[i - 1] == '1') {
                    dp[cur] = (dp[cur] + 9LL * dp[prevprev]) % M;
                } else if (s[i - 1] == '2') {
                    dp[cur] = (dp[cur] + 6LL * dp[prevprev]) % M;
                } else if (s[i - 1] == '*') {
                    dp[cur] = (dp[cur] + 15LL * dp[prevprev]) % M;
                }
            } else {
                dp[cur] = (s[i] != '0') ? dp[prev] % M : 0;
                if (s[i - 1] == '1') {
                    dp[cur] = (dp[cur] + dp[prevprev]) % M;
                } else if (s[i - 1] == '2' && s[i] <= '6') {
                    dp[cur] = (dp[cur] + dp[prevprev]) % M;
                } else if (s[i - 1] == '*') {
                    long long add = (s[i] <= '6') ? 2LL : 1LL;
                    dp[cur] = (dp[cur] + add * dp[prevprev]) % M;
                }
            }
        }
        return static_cast<int>(dp[n % W] % M);
    }
};