#include <vector>
#include <deque>

using std::vector;
using std::deque;

class Solution {
public:
    // Time:  O(n)
    // Space: O(k)
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        if (k <= 0 || nums.empty()) return result;
        deque<int> dq;
        result.reserve(nums.size() >= static_cast<size_t>(k) ? nums.size() - k + 1 : 0);
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (!dq.empty() && i - dq.front() == k) {
                dq.pop_front();
            }
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        return result;
    }
};