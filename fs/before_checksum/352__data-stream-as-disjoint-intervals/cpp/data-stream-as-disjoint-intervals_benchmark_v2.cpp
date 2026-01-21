#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <climits>

class SummaryRanges {
public:
    SummaryRanges() {}

    void addNum(int val) {
        auto upper_bound_index = [&](const std::vector<std::pair<int, int>>& nums, int target) -> int {
            int left = 0, right = static_cast<int>(nums.size()) - 1;
            while (left <= right) {
                int mid = left + ((right - left) >> 1);
                if (nums[mid].first > target) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        int i = upper_bound_index(intervals_, val);
        int start = val, end = val;

        if (i != 0) {
            long long prev_end = static_cast<long long>(intervals_[i - 1].second);
            if (prev_end + 1 >= static_cast<long long>(val)) {
                --i;
            }
        }

        while (i < static_cast<int>(intervals_.size())) {
            long long cur_start = static_cast<long long>(intervals_[i].first);
            if (static_cast<long long>(end) + 1 < cur_start) break;
            start = std::min(start, intervals_[i].first);
            end = std::max(end, intervals_[i].second);
            intervals_.erase(intervals_.begin() + i);
        }
        intervals_.insert(intervals_.begin() + i, {start, end});
    }

    std::vector<std::vector<int>> getIntervals() {
        std::vector<std::vector<int>> res;
        res.reserve(intervals_.size());
        for (const auto& p : intervals_) {
            res.push_back({p.first, p.second});
        }
        return res;
    }

private:
    std::vector<std::pair<int, int>> intervals_;
};

int main() {
    std::vector<std::vector<int>> tests = {
        {1, 2, 3, 4},
        {1, 1, 1, 2},
        {1, 3, 5, 7},
        {1, 3, 2, 6, 5, 4},
        {0, 2, 4, 3, 1},
        {9998, 10000, 9999},
        {10, 100, 1000, 10000},
        {1, 4, 7, 2, 3, 5, 6},
        {5, 5, 7, 9, 8, 6},
        {42}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            SummaryRanges sr;
            for (int v : tc) {
                sr.addNum(v);
            }
            auto res = sr.getIntervals();
            checksum += static_cast<int>(res.size());
            for (const auto& r : res) {
                checksum += r[0] + r[1];
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}