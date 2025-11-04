#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>

class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<long long> accu(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            accu[i + 1] = accu[i] + nums[i];
        }

        std::vector<int> left_pos(n, 0);
        long long total = accu[k] - accu[0];
        for (int i = k; i < n; ++i) {
            long long cur = accu[i + 1] - accu[i + 1 - k];
            if (cur > total) {
                left_pos[i] = i + 1 - k;
                total = cur;
            } else {
                left_pos[i] = left_pos[i - 1];
            }
        }

        std::vector<int> right_pos(n, n - k);
        total = accu[n] - accu[n - k];
        for (int i = n - k - 1; i >= 0; --i) {
            long long cur = accu[i + k] - accu[i];
            if (cur > total) {
                right_pos[i] = i;
                total = cur;
            } else {
                right_pos[i] = right_pos[i + 1];
            }
        }

        std::vector<int> result;
        long long max_sum = 0;
        for (int i = k; i <= n - 2 * k; ++i) {
            int left = left_pos[i - 1];
            int right = right_pos[i + k];
            long long cur = (accu[i + k] - accu[i]) +
                            (accu[left + k] - accu[left]) +
                            (accu[right + k] - accu[right]);
            if (cur > max_sum) {
                max_sum = cur;
                result = {left, i, right};
            }
        }

        return result;
    }
};