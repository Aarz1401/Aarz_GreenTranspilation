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
#include <tuple>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int countGoodArrays(int n, int m, int k) {
        long long comb = nCr(n - 1, k);
        long long powv = modpow((long long)m - 1, (long long)(n - 1 - k));
        long long res = comb * ((long long)m % MOD) % MOD;
        res = res * powv % MOD;
        return (int)res;
    }

private:
    static const int MOD = 1000000007;
    static vector<long long> FACT;
    static vector<long long> INV;
    static vector<long long> INV_FACT;

    static long long modpow(long long a, long long e) {
        a %= MOD;
        long long r = 1;
        while (e > 0) {
            if (e & 1) r = (r * a) % MOD;
            a = (a * a) % MOD;
            e >>= 1;
        }
        return r;
    }

    static void ensure(int n) {
        while ((int)INV.size() <= n) {
            int i = (int)INV.size();
            FACT.push_back(FACT.back() * i % MOD);
            long long inv_i = INV[MOD % i] * (MOD - MOD / i) % MOD;  // modular inverse of i
            INV.push_back(inv_i);
            INV_FACT.push_back(INV_FACT.back() * inv_i % MOD);
        }
    }

    static long long nCr(int n, int k) {
        if (k < 0 || k > n) return 0;
        ensure(n);
        return FACT[n] * (INV_FACT[n - k] * INV_FACT[k] % MOD) % MOD;
    }
};

vector<long long> Solution::FACT = {1, 1};
vector<long long> Solution::INV = {0, 1};
vector<long long> Solution::INV_FACT = {1, 1};
