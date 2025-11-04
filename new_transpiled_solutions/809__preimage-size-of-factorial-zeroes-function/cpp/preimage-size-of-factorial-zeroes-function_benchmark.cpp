#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdint>
#include <chrono>

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

int main() {
    // 10 diverse test inputs for K
    vector<int> test_inputs = {
        0,          // expect 5
        1,          // expect 5
        4,          // expect 5
        5,          // expect 0
        6,          // expect 5
        10,         // expect 5
        24,         // expect 0
        25,         // expect 5
        100,        // commonly 0
        1000000000  // large K for stress
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // Slightly vary inputs each iteration to avoid code motion/hoisting
        for (size_t i = 0; i < test_inputs.size(); ++i) {
            int k = test_inputs[i] + (iter & 1); // toggle between k and k+1
            int result = sol.preimageSizeFZF(k);
            checksum += result;
            checksum ^= (static_cast<long long>(k) << (i % 23));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}