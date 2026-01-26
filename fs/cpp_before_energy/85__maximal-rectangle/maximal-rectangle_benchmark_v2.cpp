#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
using namespace std;

// Time:  O(n^2)
// Space: O(n)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        int result = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> heights(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
            }
            result = max(result, largestRectangleArea(heights));
        }
        return result;
    }

private:
    int largestRectangleArea(const vector<int>& heights) {
        vector<int> stk;
        stk.push_back(-1);
        int result = 0;
        int n = heights.size();
        for (int i = 0; i <= n; ++i) {
            while (stk.back() != -1 && (i == n || heights[stk.back()] >= heights[i])) {
                int h = heights[stk.back()];
                stk.pop_back();
                int width = (i - 1) - stk.back();
                result = max(result, h * width);
            }
            stk.push_back(i);
        }
        return result;
    }
};

int main() {
    vector<vector<vector<char>>> tests = {
        { {'0'} },
        { {'1'} },
        { {'1','0','1','1','1'} },
        { {'1'},{'1'},{'0'},{'1'},{'1'} },
        { {'1','1','1'},
          {'1','1','1'},
          {'1','1','1'} },
        { {'1','0','1','0'},
          {'0','1','0','1'},
          {'1','0','1','0'},
          {'0','1','0','1'} },
        { {'1','1','1','1','0'},
          {'1','1','0','1','0'},
          {'1','1','0','1','1'},
          {'0','0','0','1','1'} },
        { {'1','0','1','0','1','1'},
          {'1','1','1','1','1','1'} },
        { {'1','1','0','1','1','1'},
          {'1','1','1','1','0','1'},
          {'0','1','1','1','1','1'},
          {'1','1','1','0','1','1'},
          {'1','1','1','1','1','0'} },
        { {'0','1','1','0','1','0'},
          {'1','1','1','1','0','1'},
          {'1','0','1','1','1','1'},
          {'0','1','0','1','1','0'},
          {'1','1','1','1','1','1'},
          {'1','0','1','0','1','1'} }
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& m : tests) {
            int r = sol.maximalRectangle(m);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}