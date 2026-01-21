#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

class Solution {
    static const int MOD = 1000000007;
    static vector<long long> FACT;
    static vector<long long> INV;
    static vector<long long> INV_FACT;

    static void ensure(int n) {
        if ((int)FACT.size() > n) return;
        int cur = FACT.size();
        FACT.reserve(n + 1);
        INV.reserve(n + 1);
        INV_FACT.reserve(n + 1);
        for (int i = cur; i <= n; ++i) {
            FACT.push_back(FACT.back() * i % MOD);
            INV.push_back(INV[MOD % i] * (MOD - MOD / i) % MOD);
            INV_FACT.push_back(INV_FACT.back() * INV.back() % MOD);
        }
    }

    static long long nCr(int n, int k) {
        if (k < 0 || k > n) return 0;
        ensure(n);
        return (((FACT[n] * INV_FACT[n - k]) % MOD) * INV_FACT[k]) % MOD;
    }

public:
    int distanceSum(int m, int n, int k) {
        if (k < 2) return 0;
        const long long inv2 = 500000004LL;     // inverse of 2 mod MOD
        const long long inv6 = 166666668LL;     // inverse of 6 mod MOD

        auto sum_n = [&](long long x) -> long long {
            x %= MOD;
            return x * ((x + 1) % MOD) % MOD * inv2 % MOD;
        };

        auto sum_n_square = [&](long long x) -> long long {
            x %= MOD;
            long long a = x * ((x + 1) % MOD) % MOD;
            long long b = (2 * x + 1) % MOD;
            return a * b % MOD * inv6 % MOD;
        };

        auto f = [&](long long x) -> long long {
            if (x <= 1) return 0LL;
            long long t1 = (x % MOD) * sum_n(x - 1) % MOD;
            long long t2 = sum_n_square(x - 1);
            long long res = (t1 - t2) % MOD;
            if (res < 0) res += MOD;
            return res;
        };

        long long term = ( (f(n) * m % MOD * m % MOD) + (f(m) * n % MOD * n % MOD) ) % MOD;
        long long total = 1LL * m * n - 2;
        long long comb = nCr((int)total, k - 2);
        long long ans = term * comb % MOD;
        return (int)ans;
    }
};

vector<long long> Solution::FACT = {1, 1};
vector<long long> Solution::INV = {0, 1};
vector<long long> Solution::INV_FACT = {1, 1};

int main() {
    vector<tuple<int,int,int>> tests = {
        {1, 1, 1},
        {1, 2, 2},
        {2, 2, 2},
        {2, 3, 3},
        {3, 3, 5},
        {5, 4, 6},
        {10, 10, 2},
        {20, 15, 10},
        {50, 40, 20},
        {100, 100, 50}
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            int m, n, k;
            tie(m, n, k) = t;
            long long res = s.distanceSum(m, n, k);
            checksum = (int)((checksum + res) % 1000000007);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}