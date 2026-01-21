#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <cstdint>
#include <chrono>

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

struct TestCase {
    int N;
    int L;
    int K;
};

int main() {
    Solution sol;

    std::vector<TestCase> tests = {
        {1, 1, 0},    // minimal case
        {2, 3, 0},    // small, K=0
        {3, 3, 1},    // L==N, K>0
        {3, 2, 0},    // L<N -> 0
        {4, 10, 2},   // moderate
        {7, 12, 5},   // K close to N
        {10, 10, 0},  // L==N, K=0
        {10, 20, 2},  // larger L
        {20, 50, 5},  // larger N and L
        {50, 100, 10} // heavier case
    };

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    unsigned long long checksum = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            checksum += static_cast<unsigned long long>(sol.numMusicPlaylists(t.N, t.L, t.K));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";

    return 0;
}