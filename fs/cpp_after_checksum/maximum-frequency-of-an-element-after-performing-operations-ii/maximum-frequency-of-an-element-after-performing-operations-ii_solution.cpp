#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>

class Solution {
public:
    int maxFrequency(std::vector<int>& nums, int k, int numOperations) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        long long result = 0;
        int left = 0, right = -1;
        std::unordered_map<long long, int> cnt;

        for (int i = 0; i < n; ++i) {
            while (right + 1 < n && static_cast<long long>(nums[right + 1]) - nums[i] <= k) {
                cnt[nums[right + 1]] += 1;
                ++right;
            }
            while (static_cast<long long>(nums[i]) - nums[left] > k) {
                auto it = cnt.find(nums[left]);
                if (it != cnt.end()) {
                    if (--(it->second) == 0) {
                        cnt.erase(it);
                    }
                }
                ++left;
            }
            int total = right - left + 1;
            int c = cnt.count(nums[i]) ? cnt[nums[i]] : 0;
            result = std::max<long long>(result, c + std::min(numOperations, total - c));
        }

        left = 0;
        for (int r = 0; r < n; ++r) {
            while (static_cast<long long>(nums[left]) + k < static_cast<long long>(nums[r]) - k) {
                ++left;
            }
            result = std::max<long long>(result, std::min(numOperations, r - left + 1));
        }

        if (result > n) result = n;
        return static_cast<int>(result);
    }
};

struct TestCase {
    std::vector<int> nums;
    int k;
    int ops;
};
