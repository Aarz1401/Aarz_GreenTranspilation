#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <array>

class Solution {
public:
    std::vector<std::vector<int>> getSkyline(std::vector<std::vector<int>>& buildings) {
        using Interval = std::array<int, 3>;
        std::vector<Interval> b;
        b.reserve(buildings.size());
        for (const auto& v : buildings) {
            b.push_back({v[0], v[1], v[2]});
        }

        std::vector<Interval> intervals = ComputeSkylineInInterval(b, 0, static_cast<int>(b.size()));

        std::vector<std::vector<int>> res;
        int last_end = -1;
        for (const auto& interval : intervals) {
            if (last_end != -1 && last_end < interval[START]) {
                res.push_back({last_end, 0});
            }
            res.push_back({interval[START], interval[HEIGHT]});
            last_end = interval[END];
        }
        if (last_end != -1) {
            res.push_back({last_end, 0});
        }
        return res;
    }

private:
    using Interval = std::array<int, 3>;
    static constexpr int START = 0;
    static constexpr int END = 1;
    static constexpr int HEIGHT = 2;

    std::vector<Interval> ComputeSkylineInInterval(const std::vector<Interval>& buildings, int left_endpoint, int right_endpoint) {
        if (right_endpoint - left_endpoint <= 1) {
            return std::vector<Interval>(buildings.begin() + left_endpoint, buildings.begin() + right_endpoint);
        }
        int mid = left_endpoint + ((right_endpoint - left_endpoint) / 2);
        std::vector<Interval> left_skyline = ComputeSkylineInInterval(buildings, left_endpoint, mid);
        std::vector<Interval> right_skyline = ComputeSkylineInInterval(buildings, mid, right_endpoint);
        return MergeSkylines(left_skyline, right_skyline);
    }

    std::vector<Interval> MergeSkylines(std::vector<Interval>& left_skyline, std::vector<Interval>& right_skyline) {
        int i = 0, j = 0;
        std::vector<Interval> merged;

        while (i < static_cast<int>(left_skyline.size()) && j < static_cast<int>(right_skyline.size())) {
            if (left_skyline[i][END] < right_skyline[j][START]) {
                merged.push_back(left_skyline[i]);
                ++i;
            } else if (right_skyline[j][END] < left_skyline[i][START]) {
                merged.push_back(right_skyline[j]);
                ++j;
            } else if (left_skyline[i][START] <= right_skyline[j][START]) {
                MergeIntersectSkylines(merged, left_skyline, i, right_skyline, j);
            } else {
                MergeIntersectSkylines(merged, right_skyline, j, left_skyline, i);
            }
        }

        while (i < static_cast<int>(left_skyline.size())) {
            merged.push_back(left_skyline[i++]);
        }
        while (j < static_cast<int>(right_skyline.size())) {
            merged.push_back(right_skyline[j++]);
        }
        return merged;
    }

    // a[START] <= b[START]
    void MergeIntersectSkylines(std::vector<Interval>& merged,
                                std::vector<Interval>& A, int& a_idx,
                                std::vector<Interval>& B, int& b_idx) {
        Interval& a = A[a_idx];
        Interval& b = B[b_idx];

        if (a[END] <= b[END]) {
            if (a[HEIGHT] > b[HEIGHT]) {  // |aaa|
                if (b[END] != a[END]) {   // |abb|b
                    b[START] = a[END];
                    merged.push_back(a);
                    ++a_idx;
                } else {                  // aaa
                    ++b_idx;              // abb
                }
            } else if (a[HEIGHT] == b[HEIGHT]) { // abb
                b[START] = a[START];             // abb
                ++a_idx;
            } else {  // a[HEIGHT] < b[HEIGHT]
                if (a[START] != b[START]) {                            //    bb
                    merged.push_back(Interval{a[START], b[START], a[HEIGHT]});  // |a|bb
                }
                ++a_idx;
            }
        } else {  // a[END] > b[END]
            if (a[HEIGHT] >= b[HEIGHT]) {  // aaaa
                ++b_idx;                   // abba
            } else {
                //    |bb|
                // |a||bb|a
                if (a[START] != b[START]) {
                    merged.push_back(Interval{a[START], b[START], a[HEIGHT]});
                }
                a[START] = b[END];
                merged.push_back(b);
                ++b_idx;
            }
        }
    }
};

int main() {
    std::vector<std::vector<std::vector<int>>> tests = {
        {{2, 9, 10}},
        {{1, 2, 1}, {3, 4, 2}},
        {{2, 6, 4}, {4, 8, 6}},
        {{1, 3, 4}, {3, 5, 4}, {5, 8, 4}},
        {{1, 4, 5}, {2, 6, 7}, {5, 8, 6}, {7, 9, 4}, {3, 5, 8}},
        {{1, 2, 1}, {2, 3, 2}, {3, 4, 3}, {4, 5, 4}, {5, 6, 5}},
        {{1, 10, 5}, {1, 7, 9}, {1, 3, 8}, {1, 5, 3}},
        {{50, 120, 5}, {100, 200, 10}, {150, 250, 20}, {240, 300, 15}, {310, 320, 10}},
        {{1, 2, 3}, {2, 4, 3}, {3, 5, 2}, {4, 6, 4}, {5, 7, 3}, {6, 8, 5}},
        {{1, 2, 1}, {10, 12, 2}, {20, 25, 3}, {30, 40, 1}}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& buildings : tests) {
            auto res = sol.getSkyline(buildings);
            DoNotOptimize(res); 
            //checksum += static_cast<int>(res.size());
        }
        //sink = checksum;
    }
    return 0;
}