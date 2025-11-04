#include <iostream>
#include <algorithm>
#include <cstdint>
#include <chrono>
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

struct TestCase {
    int N;
    int A;
    int B;
};

int main() {
    Solution sol;

    const std::vector<TestCase> tests = {
        {1, 2, 3},                      // simple small values
        {5, 2, 4},                      // one multiple of the other
        {10, 5, 5},                     // equal A and B
        {100, 3, 7},                    // coprime small
        {1000, 8, 12},                  // gcd > 1
        {100000, 1, 1000000000},        // A = 1
        {1000000, 999999937, 999999929},// large primes near 1e9
        {200000000, 40000, 39999},      // mid-large, near-coprime
        {1000000000, 2147483647, 2147483646}, // near int max
        {123456789, 12345, 67890}       // arbitrary mixed
    };

    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int res = sol.nthMagicalNumber(tests[i].N, tests[i].A, tests[i].B);
            checksum += res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    double elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}