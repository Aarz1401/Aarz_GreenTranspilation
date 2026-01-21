#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

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

int main() {
    std::vector<TestCase> tests = {
        { {5,5,5,5}, 0, 0 },
        { {1,2,3,4,5}, 0, 2 },
        { {1,1,2,2,3,3}, 1, 2 },
        { {10,20,30,40,50}, 100, 1 },
        { {-5,-3,-1,0,2,4}, 2, 3 },
        { {7}, 0, 100 },
        { {1,1,1,2,2,4,4,4,4,5,6,6,6,7,7,8}, 0, 1000 },
        { {1000000000, -1000000000, 0, 999999999, -999999999}, 2000000000, 2 },
        { {1,2,2,2,5,5,8,9,10}, 3, 2 },
        { {0,1,3,6,10,15,21,28,36,45}, 4, 5 }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            std::vector<int> nums = tc.nums;
            checksum += sol.maxFrequency(nums, tc.k, tc.ops);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}