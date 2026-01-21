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
#include <random>

using namespace std;
using namespace std::chrono;

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
    // Prepare 10 diverse test inputs
    vector<vector<int>> tests;

    // 1) Empty
    tests.push_back({});

    // 2) Single element
    tests.push_back({1});

    // 3) All ones
    tests.push_back(vector<int>(8, 1));

    // 4) Primes
    tests.push_back({2, 3, 5, 7, 11, 13, 17, 19});

    // 5) Even numbers up to 20
    tests.push_back({2, 4, 6, 8, 10, 12, 14, 16, 18, 20});

    // 6) Mixed with repeats and multiples
    tests.push_back({6, 6, 3, 9, 12, 15, 30, 45, 60});

    // 7) Deterministic random in [1, 60], size 50
    {
        mt19937 rng(123456789u);
        uniform_int_distribution<int> dist(1, 60);
        vector<int> v;
        v.reserve(50);
        for (int i = 0; i < 50; ++i) v.push_back(dist(rng));
        tests.push_back(move(v));
    }

    // 8) Powers of two with duplicates
    tests.push_back({1, 2, 4, 8, 16, 32, 64, 64, 32, 16, 8, 4, 2, 1});

    // 9) Multiples of 6 up to 60, duplicated sequence
    tests.push_back({6, 12, 18, 24, 30, 36, 42, 48, 54, 60,
                     6, 12, 18, 24, 30, 36, 42, 48, 54, 60});

    // 10) Sequence 1..80
    {
        vector<int> v;
        v.reserve(80);
        for (int i = 1; i <= 80; ++i) v.push_back(i);
        tests.push_back(move(v));
    }

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto &tc : tests) {
            checksum += sol.subsequencePairCount(tc);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}