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

struct TestCase {
    vector<int> nums;
    vector<int> target;
};

int main() {
    // Define 10 diverse test inputs
    vector<TestCase> tests;

    tests.push_back({{1}, {1}});                                               // Case 1: trivial
    tests.push_back({{2, 3, 4}, {2, 3}});                                      // Case 2: small mix
    tests.push_back({{5, 7, 11}, {6, 10, 15}});                                // Case 3: co-prime targets
    tests.push_back({{8, 16, 24, 40}, {4, 8, 2, 4}});                          // Case 4: duplicates in target
    tests.push_back({{1000000000, 999999937, 500000003}, {97, 89, 83, 79}});   // Case 5: large numbers/primes
    tests.push_back({{12, 18, 30, 42, 60}, {6, 12, 18, 24, 30}});              // Case 6: increasing multiples
    tests.push_back({{1,2,3,4,5,6,7,8,9,10}, {2,3,5,7,11}});                   // Case 7: more nums, 5 targets
    tests.push_back({{0, 0, 0}, {0, 1, 2}});                                   // Case 8: includes zeroes
    tests.push_back({{123, 456, 789, 101112}, {9, 12, 27, 36}});               // Case 9: composite targets
    tests.push_back({{13, 26, 39, 52, 65, 78}, {13, 26, 52, 104}});            // Case 10: powers/multiples

    Solution sol;
    long long checksum = 0;

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::microseconds;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.minimumIncrements(tc.nums, tc.target);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}