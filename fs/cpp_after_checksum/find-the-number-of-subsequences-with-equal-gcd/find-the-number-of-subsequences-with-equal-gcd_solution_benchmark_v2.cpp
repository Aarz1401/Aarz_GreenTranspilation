#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int subsequencePairCount(vector<int>& nums) {
        static const int MOD = 1000000007;
        if (nums.empty()) return 0;

        auto gcdll = [](long long a, long long b) {
            while (b) {
                long long t = a % b;
                a = b;
                b = t;
            }
            return a;
        };
        auto lcmll = [&](long long a, long long b) {
            long long g = gcdll(a, b);
            return (a / g) * b;
        };

        int n = (int)nums.size();
        int mx = *max_element(nums.begin(), nums.end());

        // count of numbers equal to x
        vector<int> cnt(mx + 1, 0);
        for (int x : nums) {
            if (x <= mx) cnt[x]++;
        }

        // transform to count of numbers divisible by i
        for (int i = 1; i <= mx; ++i) {
            for (int j = i + i; j <= mx; j += i) {
                cnt[i] += cnt[j];
            }
        }

        // precompute powers
        int maxPow2 = 2 * n + 5;
        int maxPow3 = n + 5;
        vector<long long> pow2(maxPow2, 1), pow3(maxPow3, 1);
        for (int i = 0; i + 1 < maxPow2; ++i) {
            pow2[i + 1] = (pow2[i] * 2) % MOD;
        }
        for (int i = 0; i + 1 < maxPow3; ++i) {
            pow3[i + 1] = (pow3[i] * 3) % MOD;
        }

        // mobius function
        vector<int> mu(mx + 1, 0);
        mu[1] = 1;
        for (int i = 1; i <= mx; ++i) {
            for (int j = i + i; j <= mx; j += i) {
                mu[j] -= mu[i];
            }
        }

        auto F = [&](int a, int b) -> long long {
            long long l = lcmll(a, b);
            int c = (l <= mx) ? cnt[(int)l] : 0;
            int c1 = cnt[a];
            int c2 = cnt[b];
            int e2 = (c1 - c) + (c2 - c);  // exponent for pow2
            long long v = 0;
            long long part1 = (pow3[c] * pow2[e2]) % MOD;
            v = part1;
            v = (v - pow2[c1]) % MOD;
            if (v < 0) v += MOD;
            v = (v - pow2[c2]) % MOD;
            if (v < 0) v += MOD;
            v = (v + 1) % MOD;
            return v;
        };

        long long ans = 0;
        for (int g = 1; g <= mx; ++g) {
            int limit = mx / g;
            long long sumg = 0;
            for (int i = 1; i <= limit; ++i) {
                if (mu[i] == 0) continue;
                for (int j = 1; j <= limit; ++j) {
                    if (mu[j] == 0) continue;
                    long long fij = F(i * g, j * g);
                    int prod = mu[i] * mu[j]; // in {-1, 0, 1}
                    if (prod == 1) {
                        sumg += fij;
                        if (sumg >= MOD) sumg -= MOD;
                    } else if (prod == -1) {
                        sumg -= fij;
                        if (sumg < 0) sumg += MOD;
                    }
                }
            }
            ans += sumg;
            if (ans >= MOD) ans -= MOD;
        }

        return (int)(ans % MOD);
    }
};

int main() {
    vector<vector<int>> tests = {
        {1},
        {1, 1, 1, 1},
        {2, 3, 4, 6},
        {2, 3, 5, 7, 11},
        {1, 2, 4, 8, 16, 32},
        {6, 12, 18, 24, 30},
        {10, 10, 10, 10, 10, 10, 10},
        {3, 6, 9, 12, 15, 21, 27},
        {4, 9, 25, 49},
        {5, 10, 20, 4, 8, 16, 3, 6, 12}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += sol.subsequencePairCount(t);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}