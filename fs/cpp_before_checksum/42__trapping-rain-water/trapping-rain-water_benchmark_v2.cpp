#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    // Time:  O(n)
    // Space: O(1)
    int trap(std::vector<int>& height) {
        long long result = 0;
        int left = 0, right = static_cast<int>(height.size()) - 1;
        int level = 0;
        while (left < right) {
            int lower;
            if (height[left] < height[right]) {
                lower = height[left];
                ++left;
            } else {
                lower = height[right];
                --right;
            }
            level = std::max(level, lower);
            result += static_cast<long long>(level - lower);
        }
        return static_cast<int>(result);
    }
};

int main() {
    std::vector<std::vector<int>> tests = {
        {0,1,0,2,1,0,1,3,2,1,2,1},
        {0,1,2,3,4,5,6,7},
        {7,6,5,4,3,2,1,0},
        {2,2,2,2,2},
        {5,0,5},
        {4,2,0,3,2,5},
        {3,0,2,0,4},
        {0,0,0,0},
        {9,1,8,0,7,2,6,3,5,4,4,5,3,6,2,7,0,8,1,9},
        {1,3,2,1,2,1,5,2,2,1,4,2,2,1,0,1,2,3,4,0,2}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& h : tests) {
            checksum += sol.trap(h);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}