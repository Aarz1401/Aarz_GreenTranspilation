#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdint>

class Solution {
public:
    int splitArray(std::vector<int>& nums, int m) {
        auto check = [&](long long s) -> bool {
            int cnt = 1;
            long long curr_sum = 0;
            for (int num : nums) {
                curr_sum += num;
                if (curr_sum > s) {
                    curr_sum = num;
                    ++cnt;
                }
            }
            return cnt <= m;
        };

        long long left = *std::max_element(nums.begin(), nums.end());
        long long right = std::accumulate(nums.begin(), nums.end(), 0LL);
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return static_cast<int>(left);
    }
};

struct TestCase {
    std::vector<int> nums;
    int m;
};

int main() {
    std::vector<TestCase> tests = {
        { {7, 2, 5, 10, 8}, 2 },
        { {5}, 1 },
        { {1, 1, 1, 1, 1}, 5 },
        { {1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 },
        { {1000000, 1000000, 1000000, 1000000}, 2 },
        { {2, 3, 1, 2, 4, 3}, 1 },
        { {9, 8, 7, 6}, 4 },
        { {5, 1, 8, 3, 2, 7, 4, 6, 9, 10, 11, 13, 12, 14, 15, 16, 18, 17, 19, 20}, 5 },
        { {0, 0, 0, 0, 0, 10}, 3 },
        { {100, 1, 100, 1, 100, 1, 100, 1, 100, 1}, 3 }
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            int r = sol.splitArray(t.nums, t.m);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}