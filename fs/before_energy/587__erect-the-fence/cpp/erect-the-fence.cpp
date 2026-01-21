#include <algorithm>
#include <cstdint>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& points) {
        // Sort the points lexicographically and remove duplicates.
        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0] || (a[0] == b[0] && a[1] < b[1]);
        });
        points.erase(unique(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] == b[0] && a[1] == b[1];
        }), points.end());

        if (points.size() <= 1) {
            return points;
        }

        auto cross = [](const vector<int>& o, const vector<int>& a, const vector<int>& b) -> long long {
            return static_cast<long long>(a[0] - o[0]) * static_cast<long long>(b[1] - o[1]) -
                   static_cast<long long>(a[1] - o[1]) * static_cast<long long>(b[0] - o[0]);
        };

        // Build lower hull
        vector<vector<int>> lower;
        for (const auto& p : points) {
            while (lower.size() >= 2 &&
                   cross(lower[lower.size() - 2], lower[lower.size() - 1], p) < 0) { // modified
                lower.pop_back();
            }
            lower.push_back(p);
        }

        // Build upper hull
        vector<vector<int>> upper;
        for (int i = static_cast<int>(points.size()) - 1; i >= 0; --i) {
            const auto& p = points[i];
            while (upper.size() >= 2 &&
                   cross(upper[upper.size() - 2], upper[upper.size() - 1], p) < 0) { // modified
                upper.pop_back();
            }
            upper.push_back(p);
        }

        // Concatenate lower and upper hulls (omit last point of each because it repeats)
        vector<vector<int>> result;
        if (!lower.empty()) {
            result.insert(result.end(), lower.begin(), lower.end() - 1);
        }
        if (!upper.empty()) {
            result.insert(result.end(), upper.begin(), upper.end() - 1);
        }

        if (result.size() <= 1) return result;
        if (!(result[1][0] == result.back()[0] && result[1][1] == result.back()[1])) {
            return result;
        } else {
            size_t k = result.size() / 2 + 1;
            return vector<vector<int>>(result.begin(), result.begin() + k);
        }
    }
};