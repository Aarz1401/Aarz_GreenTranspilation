#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <cstdint>

class Solution {
public:
    int checkRecord(int n) {
        const int MOD = 1000000007;
        long long a0l0 = 1, a0l1 = 0, a0l2 = 0;
        long long a1l0 = 0, a1l1 = 0, a1l2 = 0;
        for (int i = 0; i <= n; ++i) {
            long long na0l2 = a0l1;
            long long na0l1 = a0l0;
            long long na0l0 = (a0l0 + a0l1 + a0l2) % MOD;

            long long na1l2 = a1l1;
            long long na1l1 = a1l0;
            long long na1l0 = (na0l0 + a1l0 + a1l1 + a1l2) % MOD;

            a0l2 = na0l2; a0l1 = na0l1; a0l0 = na0l0;
            a1l2 = na1l2; a1l1 = na1l1; a1l0 = na1l0;
        }
        return static_cast<int>(a1l0);
    }
};