#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <utility>

class Solution {
public:
    int findKthNumber(int n, int k) {
        long long result = 0;

        // Precompute counts
        std::vector<long long> cnts(11, 0);
        for (int i = 1; i <= 10; ++i) {
            cnts[i] = cnts[i - 1] * 10 + 1;
        }

        // Extract digits of n (least significant first)
        std::vector<int> nums;
        long long temp = n;
        while (temp) {
            nums.push_back(static_cast<int>(temp % 10));
            temp /= 10;
        }

        long long total = n, target = 0;
        int i = static_cast<int>(nums.size()) - 1;
        long long kk = k;
        while (i >= 0 && kk > 0) {
            target = target * 10 + nums[i];
            int start = (i == static_cast<int>(nums.size()) - 1) ? 1 : 0;
            for (int j = start; j <= 9; ++j) {
                long long candidate = result * 10 + j;
                long long num = 0;
                if (candidate < target) {
                    num = cnts[i + 1];
                } else if (candidate > target) {
                    num = cnts[i];
                } else {
                    num = total - cnts[i + 1] * (j - start) - cnts[i] * (9 - j);
                }
                if (kk > num) {
                    kk -= num;
                } else {
                    result = candidate;
                    kk -= 1;
                    total = num - 1;
                    break;
                }
            }
            --i;
        }

        return static_cast<int>(result);
    }
};

int main() {
    std::vector<std::pair<int,int>> tests = {
        {1, 1},
        {13, 2},
        {13, 6},
        {100, 90},
        {1000, 1},
        {1000, 1000},
        {1000000, 123456},
        {1000000000, 1},
        {1000000000, 1000000000},
        {123456789, 98765432}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            int r = sol.findKthNumber(t.first, t.second);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}