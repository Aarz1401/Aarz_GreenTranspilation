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
#include <functional>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int goodSubtreeSum(vector<int>& vals, vector<int>& par) {
        const long long MOD = 1000000007LL;
        const long long NEG = LLONG_MIN / 4;
        int n = vals.size();
        vector<vector<int>> adj(n);
        for (int u = 1; u < n; ++u) {
            adj[par[u]].push_back(u);
        }

        auto get_mask = [&](long long x) -> int {
            int mask = 0;
            while (x) {
                int d = x % 10;
                if (mask & (1 << d)) {
                    return -1;
                }
                mask |= 1 << d;
                x /= 10;
            }
            return mask;
        };

        vector<int> masks(n, -1);
        for (int i = 0; i < n; ++i) {
            masks[i] = get_mask(vals[i]);
        }

        long long result = 0;

        function<vector<long long>(int)> dfs = [&](int u) -> vector<long long> {
            vector<long long> dp(1024, NEG);
            dp[0] = 0;
            if (masks[u] != -1) {
                dp[masks[u]] = max(dp[masks[u]], (long long)vals[u]);
            }
            for (int v : adj[u]) {
                vector<long long> child = dfs(v);
                vector<long long> ndp = dp;
                for (int m1 = 0; m1 < 1024; ++m1) {
                    if (dp[m1] == NEG) continue;
                    for (int m2 = 0; m2 < 1024; ++m2) {
                        if (child[m2] == NEG) continue;
                        if (m1 & m2) continue;
                        long long val = dp[m1] + child[m2];
                        int nm = m1 | m2;
                        if (val > ndp[nm]) {
                            ndp[nm] = val;
                        }
                    }
                }
                dp.swap(ndp);
            }
            long long best = 0;
            for (long long x : dp) {
                if (x > best) best = x;
            }
            result = (result + (best % MOD + MOD) % MOD) % MOD;
            return dp;
        };

        dfs(0);
        return (int)(result % MOD);
    }
};

struct TestCase {
    vector<int> vals;
    vector<int> par;
};

int main() {
    // Define 10 diverse single-node test cases to keep benchmark efficient
    vector<TestCase> tests;
    tests.push_back({{7}, {0}});               // single digit
    tests.push_back({{0}, {0}});               // zero value
    tests.push_back({{11}, {0}});              // repeated digit (invalid mask)
    tests.push_back({{98}, {0}});              // two unique digits
    tests.push_back({{101}, {0}});             // repeated digit (invalid mask)
    tests.push_back({{1234}, {0}});            // multiple unique digits
    tests.push_back({{1000000000}, {0}});      // many repeated zeros (invalid mask)
    tests.push_back({{24680}, {0}});           // even digits including zero
    tests.push_back({{13579}, {0}});           // odd digits
    tests.push_back({{987654321}, {0}});       // long unique digits

    Solution sol;

    volatile long long checksum = 0;

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::microseconds;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.goodSubtreeSum(const_cast<vector<int>&>(tc.vals),
                                           const_cast<vector<int>&>(tc.par));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed << "\n";

    return 0;
}