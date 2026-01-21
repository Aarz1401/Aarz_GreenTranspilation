#include <iostream>
#include <algorithm>
#include <vector>

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

int main() {
    Solution sol;
    const std::vector<std::vector<int>> tests = {
        {1, 2, 3},
        {5, 2, 4},
        {1000000000, 2, 3},
        {999999937, 40000, 39999},
        {123456789, 7, 11},
        {987654321, 6, 9},
        {500000000, 40000, 40000},
        {42, 999, 1000},
        {10, 7, 13},
        {214748364, 32768, 16384}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.nthMagicalNumber(t[0], t[1], t[2]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}