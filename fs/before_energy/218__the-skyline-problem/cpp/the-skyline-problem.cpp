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