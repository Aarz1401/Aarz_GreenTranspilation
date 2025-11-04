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