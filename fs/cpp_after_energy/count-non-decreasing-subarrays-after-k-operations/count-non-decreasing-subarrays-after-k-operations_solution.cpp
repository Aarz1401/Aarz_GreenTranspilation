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
#include <deque>
#include <chrono>

class Solution {
private:
    long long solve(std::vector<int>& nums, long long k) {
        long long result = 0;
        long long cnt = 0;
        std::deque<int> dq;
        int n = static_cast<int>(nums.size());
        int right = n - 1;
        for (int left = n - 1; left >= 0; --left) {
            while (!dq.empty() && nums[dq.back()] < nums[left]) {
                int l = dq.back();
                dq.pop_back();
                int r = !dq.empty() ? dq.back() - 1 : right;
                cnt += 1LL * (r - l + 1) * (nums[left] - nums[l]);
            }
            dq.push_back(left);
            while (cnt > k) {
                cnt -= static_cast<long long>(nums[dq.front()]) - nums[right];
                if (dq.front() == right) {
                    dq.pop_front();
                }
                --right;
            }
            result += (right - left + 1);
        }
        return result;
    }
public:
    long long countNonDecreasingSubarrays(std::vector<int>& nums, long long k) {
        return solve(nums, k);
    }
    long long countNonDecreasingSubarrays(std::vector<int>& nums, int k) {
        return solve(nums, static_cast<long long>(k));
    }
};
