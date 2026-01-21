#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <utility>

using namespace std;

// Time:  O(n^2), could be improved to O(nlogn) in cpp by ordered map (bst)
// Space: O(n)
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> result;
        vector<int> pos = {-1};
        vector<int> heights = {0};
        int maxH = 0;
        for (const auto& p : positions) {
            int left = p[0];
            int side = p[1];

            int l = static_cast<int>(upper_bound(pos.begin(), pos.end(), left) - pos.begin());
            int r = static_cast<int>(lower_bound(pos.begin(), pos.end(), left + side) - pos.begin());

            int highBase = 0;
            int start = l - 1;
            int end = r - 1;
            if (start <= end) {
                for (int i = start; i <= end; ++i) {
                    highBase = max(highBase, heights[i]);
                }
            }
            int high = highBase + side;

            int rightHeight = heights[r - 1];

            pos.erase(pos.begin() + l, pos.begin() + r);
            pos.insert(pos.begin() + l, left + side);
            pos.insert(pos.begin() + l, left);

            heights.erase(heights.begin() + l, heights.begin() + r);
            heights.insert(heights.begin() + l, rightHeight);
            heights.insert(heights.begin() + l, high);

            maxH = max(maxH, high);
            result.push_back(maxH);
        }
        return result;
    }
};