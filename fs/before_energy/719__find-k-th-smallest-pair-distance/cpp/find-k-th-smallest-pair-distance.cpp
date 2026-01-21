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