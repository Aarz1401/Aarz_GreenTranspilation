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

int main() {
    // Define 10 diverse test inputs (n, m, k)
    vector<tuple<int, int, int>> tests = {
        {1, 1, 0},            // minimal case
        {5, 3, 2},            // small typical
        {10, 1000, 0},        // k = 0
        {50, 2, 49},          // k = n - 1
        {1000, 1000000000, 500}, // large m, medium n
        {200000, 100000, 100000}, // large n
        {2, 1000000007, 1},   // m = MOD
        {100000, 1, 0},       // m = 1
        {3, 2, 1},            // small mixed
        {7, 5, 7}             // k > n - 1 -> zero combinations
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            int n, m, k;
            tie(n, m, k) = t;
            int res = sol.countGoodArrays(n, m, k);
            // Mix into checksum to avoid optimization
            checksum ^= (static_cast<unsigned long long>(res) + 0x9e3779b97f4a7c15ULL + (checksum << 6) + (checksum >> 2));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}