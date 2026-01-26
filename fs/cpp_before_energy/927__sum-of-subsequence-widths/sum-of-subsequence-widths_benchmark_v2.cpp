#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>

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

int main() {
    std::vector<std::vector<int>> tests = {
        {1},
        {1, 2},
        {5, 5},
        {2, 2, 2, 2, 2},
        {4, 1, 3, 2},
        {1000000000, 1, 1000000000},
        {1000000000, 999999999, 123456789, 987654321},
        {7, 7, 3, 1, 9, 9, 5},
        {10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
        {42, 42, 42, 1, 2, 3, 100, 1000000000, 999999999, 12345, 67890}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            std::vector<int> v = t;
            int res = sol.sumSubseqWidths(v);
            DoNotOptimize(res);
            //checksum = (checksum + res) % 1000000007;
        }
        //sink = checksum;
    }

    return 0;
}