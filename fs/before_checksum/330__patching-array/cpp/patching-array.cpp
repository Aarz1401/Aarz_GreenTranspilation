#include <iostream>
#include <vector>
#include <cstdint>

// Time:  O(s + logn), s is the number of elements in the array
// Space: O(1)
class Solution {
public:
    int minPatches(std::vector<int>& nums, int n) {
        long long miss = 1;
        int i = 0;
        int patches = 0;
        while (miss <= static_cast<long long>(n)) {
            if (i < static_cast<int>(nums.size()) && nums[i] <= miss) {
                miss += nums[i];
                ++i;
            } else {
                miss += miss;
                ++patches;
            }
        }
        return patches;
    }
};