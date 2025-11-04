#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>

// Time:  O(n^2)
// Space: O(n)

// Definition for a point.
// struct Point {
//     int x;
//     int y;
//     Point() : x(0), y(0) {}
//     Point(int a, int b) : x(a), y(b) {}
// };

class Solution {
public:
    int maxPoints(std::vector<Point>& points) {
        int n = static_cast<int>(points.size());
        if (n == 0) return 0;

        int max_points = 0;
        for (int i = 0; i < n; ++i) {
            std::unordered_map<double, int> slope_count;
            int same = 1;

            const Point& start = points[i];
            for (int j = i + 1; j < n; ++j) {
                const Point& end = points[j];
                if (start.x == end.x && start.y == end.y) {
                    ++same;
                } else {
                    double slope = std::numeric_limits<double>::infinity();
                    if (start.x != end.x) {
                        slope = static_cast<double>(start.y - end.y) /
                                static_cast<double>(start.x - end.x);
                    }
                    ++slope_count[slope];
                }
            }

            int current_max = same;
            for (const auto& kv : slope_count) {
                current_max = std::max(current_max, kv.second + same);
            }
            max_points = std::max(max_points, current_max);
        }

        return max_points;
    }
};