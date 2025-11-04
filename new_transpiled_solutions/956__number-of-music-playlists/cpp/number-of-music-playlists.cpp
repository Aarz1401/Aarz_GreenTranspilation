#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>

class Solution {
public:
    int numMusicPlaylists(int N, int L, int K) {
        const int M = 1000000007;
        if (L < N) return 0;
        std::vector<std::vector<long long>> dp(2, std::vector<long long>(L + 1, 0));
        dp[0][0] = 1;
        for (int n = 1; n <= N; ++n) {
            int cur = n & 1;
            int prev = (n - 1) & 1;
            std::fill(dp[cur].begin(), dp[cur].end(), 0LL);
            dp[cur][n] = (dp[prev][n - 1] * n) % M;
            for (int l = n + 1; l <= L; ++l) {
                long long add_new = (dp[prev][l - 1] * n) % M;
                int replay_choices = std::max(n - K, 0);
                long long extend = (dp[cur][l - 1] * replay_choices) % M;
                dp[cur][l] = (extend + add_new) % M;
            }
        }
        return static_cast<int>(dp[N & 1][L] % M);
    }
};