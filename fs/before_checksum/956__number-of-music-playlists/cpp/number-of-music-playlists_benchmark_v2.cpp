#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

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

int main() {
    std::vector<std::array<int, 3>> tests = {
        std::array<int,3>{1, 1, 0},
        std::array<int,3>{2, 2, 1},
        std::array<int,3>{2, 3, 0},
        std::array<int,3>{3, 3, 2},
        std::array<int,3>{3, 4, 1},
        std::array<int,3>{3, 5, 1},
        std::array<int,3>{4, 4, 3},
        std::array<int,3>{4, 6, 2},
        std::array<int,3>{5, 7, 0},
        std::array<int,3>{6, 8, 1}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.numMusicPlaylists(t[0], t[1], t[2]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}