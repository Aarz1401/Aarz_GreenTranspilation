#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

// Time:  O((logn)^2)
// Space: O(1)

class Solution {
public:
    int preimageSizeFZF(int K) {
        auto count_of_factorial_primes = [](long long n, long long p) -> long long {
            long long cnt = 0;
            while (n > 0) {
                n /= p;
                cnt += n;
            }
            return cnt;
        };

        const long long p = 5;
        long long left = 0, right = p * static_cast<long long>(K);
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (count_of_factorial_primes(mid, p) >= K) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return (count_of_factorial_primes(left, p) == K) ? 5 : 0;
    }
};