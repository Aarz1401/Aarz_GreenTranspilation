#include <iostream>
#include <algorithm>
#include <cstdint>

class Solution {
public:
    int nthMagicalNumber(int N, int A, int B) {
        const int MOD = 1000000007;

        auto gcdll = [](long long a, long long b) -> long long {
            while (b) {
                long long t = a % b;
                a = b;
                b = t;
            }
            return a;
        };

        long long a = static_cast<long long>(A);
        long long b = static_cast<long long>(B);
        long long n = static_cast<long long>(N);

        long long g = gcdll(a, b);
        __int128 lcm = (__int128)(a / g) * (__int128)b;

        long long left = std::min(a, b);
        long long right = std::max(a, b) * n;

        while (left <= right) {
            long long mid = left + (right - left) / 2;
            __int128 count = (__int128)mid / a + (__int128)mid / b - (__int128)mid / lcm;
            if (count >= n) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return static_cast<int>(left % MOD);
    }
};