#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    vector<vector<vector<int>>> tests = {
        { {5,5} },
        { {0,0}, {3,4} },
        { {0,0}, {1,1}, {2,2}, {3,3}, {4,4} },
        { {0,0}, {0,10}, {10,10}, {10,0} },
        { {0,0}, {2,0}, {4,0}, {4,2}, {4,4}, {2,4}, {0,4}, {0,2}, {2,2}, {2,0}, {0,4} },
        { {50,60}, {57,57}, {60,50}, {57,43}, {50,40}, {43,43}, {40,50}, {43,57}, {50,50}, {55,50} },
        { {0,0}, {2,0}, {4,0}, {6,0}, {8,0}, {10,0}, {0,5}, {5,7}, {10,5}, {5,0} },
        { {1,3}, {2,8}, {3,3}, {5,5}, {7,2}, {6,9}, {10,10}, {12,1}, {9,4}, {4,7} },
        { {10,0}, {20,5}, {20,15}, {10,20}, {0,15}, {0,5}, {10,10}, {5,10}, {15,10}, {10,5} },
        { {0,0}, {20,0}, {40,0}, {60,0}, {80,0}, {100,0}, {100,10}, {80,10}, {60,10}, {40,10}, {20,10}, {0,10}, {50,0}, {50,10} }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<vector<int>> pts = tests[i];
            vector<vector<int>> out = sol.outerTrees(pts);
            DoNotOptimize(out);
            // for (const auto& p : out) {
            //     checksum += p[0] + p[1];
            // }
        }
        //sink = checksum;
    }

    return 0;
}