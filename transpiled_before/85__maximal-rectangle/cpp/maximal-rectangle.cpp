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