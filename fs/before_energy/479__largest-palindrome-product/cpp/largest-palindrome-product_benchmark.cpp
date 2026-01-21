#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <chrono>

using namespace std;

// Time:  O(n * 10^n)
// Space: O(n)
class Solution {
public:
    int largestPalindrome(int n) {
        if (n == 1) {
            return 9;
        }
        // let x = 10^n-i, y = 10^n-j, s.t. palindrome = x*y
        // => (10^n-i)*(10^n-j) = (10^n-i-j)*10^n + i*j
        // assume i*j < 10^n (in fact, it only works for 2 <= n <= 8, not general),
        // let left = (10^n-i-j), right = i*j, k = i+j
        // => left = 10^n-k, right = i*(k-i)
        // => i^2 - k*i + right = 0
        // => i = (k+(k^2-right*4)^(0.5))/2 or (k+(k^2-right*4)^(0.5))/2 where i is a positive integer
        long long pow10 = 1;
        for (int i = 0; i < n; ++i) {
            pow10 *= 10;
        }
        long long upper = pow10 - 1;

        for (long long k = 2; k <= upper; ++k) {
            long long left = pow10 - k;
            string s = to_string(left);
            reverse(s.begin(), s.end());
            long long right = stoll(s);
            long long d = k * k - 4 * right;
            if (d < 0) {
                continue;
            }
            long long r = static_cast<long long>(sqrtl(static_cast<long double>(d)));
            if (r * r == d && (k % 2) == (r % 2)) {
                long long palindrome = left * pow10 + right;
                return static_cast<int>(palindrome % 1337);
            }
        }
        return -1;
    }
};


// Time:  O(10^(2n))
// Space: O(n)
class Solution2 {
public:
    int largestPalindrome(int n) {
        auto divide_ceil = [](long long a, long long b) -> long long {
            return (a + b - 1) / b;
        };

        if (n == 1) {
            return 9;
        }
        long long pow10 = 1;
        for (int i = 0; i < n; ++i) pow10 *= 10;
        long long upper = pow10 - 1, lower = pow10 / 10;

        for (long long i = (upper * upper) / pow10; i >= lower; --i) {
            string s = to_string(i);
            string rs = s;
            reverse(rs.begin(), rs.end());
            long long candidate = stoll(s + rs);

            long long y_end = divide_ceil(lower, 11) * 11;
            long long y_start = (upper / 11) * 11;
            for (long long y = y_start; y >= y_end; y -= 11) {  // y must be divisible by 11 because even-number-length palindrome meets modulo 11 digit check
                if (candidate / y > upper) {
                    break;
                }
                if (candidate % y == 0) {
                    long long other = candidate / y;
                    if (other >= lower && other <= upper) {
                        return static_cast<int>(candidate % 1337);
                    }
                }
            }
        }
        return -1;
    }
};

int main() {
    // Define 10 diverse test inputs (within the expected range 1..8 for performance)
    vector<int> test_inputs = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    Solution sol;
    volatile long long checksum = 0; // volatile to help prevent aggressive optimization

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int n : test_inputs) {
            checksum += sol.largestPalindrome(n);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (nanoseconds): " << elapsed_ns << "\n";
    return 0;
}