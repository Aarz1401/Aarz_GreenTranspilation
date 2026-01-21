#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>

class Solution {
public:
    // Time:  O(nlogn + nlogw), n = len(nums), w = max(nums)-min(nums)
    // Space: O(1)
    int smallestDistancePair(std::vector<int>& nums, int k) {
        // Sliding window solution with binary search over answer
        std::sort(nums.begin(), nums.end());
        int left = 0;
        int right = nums.back() - nums.front() + 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (possible(mid, nums, k)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return left;
    }

private:
    static bool possible(int guess, const std::vector<int>& nums, int k) {
        long long count = 0;
        int left = 0;
        for (int right = 0; right < static_cast<int>(nums.size()); ++right) {
            while (nums[right] - nums[left] > guess) {
                ++left;
            }
            count += right - left;
        }
        return count >= static_cast<long long>(k);
    }
};

int main() {
    struct Test {
        std::vector<int> nums;
        int k;
    };

    std::vector<Test> tests = {
        {{1, 100}, 1},
        {{1, 3, 1}, 1},
        {{1, 2, 3, 4, 5}, 4},
        {{10, 10, 10, 10}, 6},
        {{1, 6, 1, 2, 5, 9}, 7},
        {{0, 0, 0, 0, 0, 0}, 10},
        {{0, 1000000}, 1},
        {{1, 1, 2, 2, 3, 3, 4, 4}, 16},
        {{1, 3, 6, 10, 15, 21, 28, 36}, 20},
        {{4, 1, 4, 2, 8, 5, 7, 2, 3}, 12}
    };

    Solution solution;

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            std::vector<int> nums = t.nums;
            int result = solution.smallestDistancePair(nums, t.k);
            DoNotOptimize(result);
            //checksum += result;
        }
        //sink = checksum;
    }

    return 0;
}