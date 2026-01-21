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
#include <cstdint>
#include <chrono>

using namespace std;

class Solution {
public:
    int countBalancedPermutations(string num) {
        const int MOD = 1000000007;

        // Combinatorics with lazy initialization
        vector<long long> fact(2, 1), inv(2, 1), inv_fact(2, 1);

        auto ensure_size = [&](int n) {
            while ((int)inv.size() <= n) {
                int i = inv.size();
                fact.push_back(fact.back() * i % MOD);
                long long inv_i = inv[MOD % i] * (MOD - MOD / i) % MOD;
                inv.push_back(inv_i);
                inv_fact.push_back(inv_fact.back() * inv_i % MOD);
            }
        };

        auto nCr = [&](int n, int k) -> long long {
            if (k < 0 || k > n) return 0;
            ensure_size(n);
            return (((fact[n] * inv_fact[n - k]) % MOD) * inv_fact[k]) % MOD;
        };

        auto factorial = [&](int n) -> long long {
            ensure_size(n);
            return fact[n];
        };

        auto inv_factorial = [&](int n) -> long long {
            ensure_size(n);
            return inv_fact[n];
        };

        int total = 0;
        for (char x : num) {
            total += (x - '0');
        }
        if (total % 2) {
            return 0;
        }
        total /= 2;

        vector<int> cnt(10, 0);
        for (char x : num) {
            cnt[x - '0']++;
        }

        int n = (int)num.size();
        int even = n / 2;

        vector<vector<int>> dp(total + 1, vector<int>(even + 1, 0));
        dp[0][0] = 1;

        for (int i = 0; i <= 9; ++i) {
            int x = cnt[i];
            if (x == 0) continue;
            for (int j = total; j >= 0; --j) {
                for (int k = even; k >= 0; --k) {
                    if (dp[j][k] == 0) continue;
                    for (int c = 1; c <= x; ++c) {
                        long long nj = j + 1LL * c * i;
                        int nk = k + c;
                        if (nj <= total && nk <= even) {
                            long long add = (1LL * dp[j][k] * nCr(x, c)) % MOD;
                            dp[(int)nj][nk] = (dp[(int)nj][nk] + (int)add) % MOD;
                        }
                    }
                }
            }
        }

        long long result = dp[total][even];
        result = result * factorial(even) % MOD;
        result = result * factorial(n - even) % MOD;
        long long denom = 1;
        for (int x : cnt) {
            denom = denom * inv_factorial(x) % MOD;
        }
        result = result * denom % MOD;

        return (int)result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse test inputs (strings of digits as required by the solution)
    vector<string> tests;
    tests.reserve(10);
    tests.push_back("0");                          // trivial, sum=0
    tests.push_back("12");                         // small even length
    tests.push_back("123");                        // odd length
    tests.push_back("00112233");                   // repeats with zeros
    tests.push_back("999999");                     // all same, large digit
    tests.push_back("3141592653");                 // mixed digits length 10
    tests.push_back("55555");                      // odd sum -> immediate 0
    tests.push_back("9876543210");                 // digits 0..9 sum odd -> 0
    tests.push_back("1111111111");                 // many ones
    tests.push_back("00000000000000000000");       // many zeros

    Solution sol;
    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // test code here
        for (const auto& s : tests) {
            int ans = sol.countBalancedPermutations(s);
            checksum = (checksum * 1315423911ULL + static_cast<unsigned long long>(ans)) ^ 0x9e3779b97f4a7c15ULL;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    double elapsed_ms = chrono::duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed(ms): " << elapsed_ms << "\n";
    return 0;
}