#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <chrono>

// Time:  O(m * log(m * n))
// Space: O(1)

class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        auto count = [&](long long target) -> long long {
            long long cnt = 0;
            for (int i = 1; i <= m; ++i) {
                cnt += std::min<long long>(target / i, n);
            }
            return cnt;
        };

        long long left = 1, right = 1LL * m * n;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (count(mid) >= k) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return static_cast<int>(left);
    }
};

struct TestCase {
    int m;
    int n;
    int k;
};

int main() {
    std::vector<TestCase> tests = {
        {1, 1, 1},
        {1, 10, 7},
        {10, 1, 3},
        {3, 3, 5},
        {10, 10, 50},
        {45, 37, 800},
        {100, 100, 5000},
        {300, 500, 120000},
        {500, 300, 75000},
        {1000, 1000, 500000}
    };

    Solution solver;
    volatile long long checksum = 0; // volatile to further prevent optimization

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            int result = solver.findKthNumber(t.m, t.n, t.k);
            checksum += result;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}