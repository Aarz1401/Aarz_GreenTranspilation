#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <stack>
#include <algorithm>
#include <cstdint>

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

// Time:  O(n)
// Space: O(1)
class Solution2 {
public:
    // @param A, a list of integers
    // @return an integer
    int trap(std::vector<int>& A) {
        if (A.empty()) return 0;
        long long result = 0;

        int top = 0;
        for (int i = 0; i < static_cast<int>(A.size()); ++i) {
            if (A[top] < A[i]) {
                top = i;
            }
        }

        int second_top = 0;
        for (int i = 0; i < top; ++i) {
            if (A[second_top] < A[i]) {
                second_top = i;
            }
            result += static_cast<long long>(A[second_top] - A[i]);
        }

        second_top = static_cast<int>(A.size()) - 1;
        for (int i = static_cast<int>(A.size()) - 1; i >= top; --i) {
            if (A[second_top] < A[i]) {
                second_top = i;
            }
            result += static_cast<long long>(A[second_top] - A[i]);
        }

        return static_cast<int>(result);
    }
};

// Time:  O(n)
// Space: O(n)
class Solution3 {
public:
    int trap(std::vector<int>& height) {
        int n = static_cast<int>(height.size());
        if (n == 0) return 0;

        std::vector<int> right(n, 0);
        int mx = 0;
        for (int i = n - 1; i >= 0; --i) {
            right[i] = mx;
            mx = std::max(mx, height[i]);
        }
        long long result = 0;
        int left = 0;
        for (int i = 0; i < n; ++i) {
            left = std::max(left, height[i]);
            int water = std::min(left, right[i]) - height[i];
            if (water > 0) result += water;
        }
        return static_cast<int>(result);
    }
};

// Time:  O(n)
// Space: O(n)
class Solution4 {
public:
    int trap(std::vector<int>& height) {
        long long result = 0;
        std::vector<int> stk;
        for (int i = 0; i < static_cast<int>(height.size()); ++i) {
            int prev = 0;
            while (!stk.empty() && height[stk.back()] <= height[i]) {
                int j = stk.back();
                stk.pop_back();
                result += static_cast<long long>(height[j] - prev) * (i - j - 1);
                prev = height[j];
            }
            if (!stk.empty()) {
                result += static_cast<long long>(height[i] - prev) * (i - stk.back() - 1);
            }
            stk.push_back(i);
        }
        return static_cast<int>(result);
    }
};