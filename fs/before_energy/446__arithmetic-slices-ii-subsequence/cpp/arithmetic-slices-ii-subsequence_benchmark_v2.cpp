#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <unordered_map>
#include <cstdint>

class Solution {
public:
    int numberOfArithmeticSlices(std::vector<int>& A) {
        // Time:  O(n^2)
        // Space: O(n * d)
        int n = static_cast<int>(A.size());
        long long result = 0;
        std::vector<std::unordered_map<long long, long long>> dp(n);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                long long diff = static_cast<long long>(A[i]) - static_cast<long long>(A[j]);
                long long cnt = 0;
                auto it = dp[j].find(diff);
                if (it != dp[j].end()) {
                    cnt = it->second;
                }
                result += cnt;               // count subsequences extended to length >= 3
                dp[i][diff] += cnt + 1;      // +1 accounts for the pair (j, i)
            }
        }
        return static_cast<int>(result);
    }
};

int main() {
    std::vector<std::vector<int>> tests = {
        {1, 2, 3},
        {2, 4, 6, 8, 10},
        {7, 7, 7, 7, 7},
        {1, 1, 2, 2, 3, 3},
        {1, 3, 5, 7, 9, 11, 13},
        {1, 5, 9, 2, 6, 10, 3, 7, 11},
        {0, -1, -2, -3, -4},
        {1, 2, 4, 8, 16, 32},
        {1000000000, -1000000000, 0, -1000000000, 1000000000},
        {1, 4, 7, 10, 13, 2, 5, 8, 11, 14, 17, 20}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& A : tests) {
            int r = sol.numberOfArithmeticSlices(A);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}