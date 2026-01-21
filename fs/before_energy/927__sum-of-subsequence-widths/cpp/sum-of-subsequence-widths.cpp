#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <cstdint>

class Solution {
public:
    int sumSubseqWidths(std::vector<int>& A) {
        // Time:  O(n)
        // Spce:  O(1)
        const long long M = 1000000007LL;
        // sum(A[i] * (2^i - 2^(len(A)-1-i))), i = 0..len(A)-1
        // <=>
        // sum(((A[i] - A[len(A)-1-i]) * 2^i), i = 0..len(A)-1
        long long result = 0;
        long long c = 1;
        std::sort(A.begin(), A.end());
        int n = static_cast<int>(A.size());
        for (int i = 0; i < n; ++i) {
            long long diff = (static_cast<long long>(A[i]) - A[n - 1 - i]) % M;
            diff = (diff + M) % M;  // ensure non-negative
            long long add = (diff * c) % M;
            result = (result + add) % M;
            c = (c * 2) % M;
        }
        return static_cast<int>(result);
    }
};