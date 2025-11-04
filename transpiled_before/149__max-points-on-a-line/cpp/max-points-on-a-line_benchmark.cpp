#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <chrono>

struct Point {
    int x;
    int y;
    Point() : x(0), y(0) {}
    Point(int a, int b) : x(a), y(b) {}
};

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

static std::vector<std::vector<Point>> create_tests() {
    std::vector<std::vector<Point>> tests;

    // 0) Empty input
    tests.push_back({});

    // 1) Single point
    tests.push_back({Point(0, 0)});

    // 2) Two points
    tests.push_back({Point(0, 0), Point(1, 1)});

    // 3) Vertical line
    tests.push_back({Point(2, 1), Point(2, 3), Point(2, 4), Point(2, -1), Point(2, 100)});

    // 4) Horizontal line with a duplicate
    tests.push_back({Point(-3, 5), Point(-1, 5), Point(0, 5), Point(2, 5), Point(2, 5), Point(10, 5)});

    // 5) Diagonal slope 1 (includes negatives and a large negative)
    tests.push_back({Point(0, 0), Point(1, 1), Point(2, 2), Point(3, 3), Point(-1000000, -1000000), Point(5, 0)});

    // 6) All duplicates of the same point
    tests.push_back({Point(7, 7), Point(7, 7), Point(7, 7), Point(7, 7), Point(7, 7)});

    // 7) Many duplicates plus others on the same line
    tests.push_back({Point(1, 1), Point(1, 1), Point(1, 1), Point(2, 2), Point(3, 3), Point(4, 5)});

    // 8) Random scatter (no three collinear)
    tests.push_back({Point(0, 1), Point(1, 3), Point(2, 7), Point(3, 12), Point(4, 20), Point(-1, -3)});

    // 9) Fractional slope 0.5 line with outlier
    tests.push_back({Point(0, 0), Point(2, 1), Point(4, 2), Point(6, 3), Point(1, 10)});

    return tests;
}

int main() {
    using namespace std;
    using namespace std::chrono;

    Solution sol;
    auto tests = create_tests();

    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int result = sol.maxPoints(tests[i]);
            // Mix in iteration and index to the checksum
            checksum += static_cast<long long>(result) + static_cast<long long>(iter & 1) + static_cast<long long>(i);
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}