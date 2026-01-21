#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdint>
#include <climits>
#include <chrono>

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
    // Define 10 diverse test inputs
    std::vector<std::vector<int>> tests = {
        {1,2,3,4,5,6,7,8,9,10},                 // increasing consecutive
        {1,3,7,2,6},                             // random with gaps and merges
        {5,5,6,4,4,7},                           // duplicates and merges
        {10,9,8,7,6,5},                          // decreasing order
        {INT_MIN, INT_MIN+1, INT_MAX-1, INT_MAX},// extremes
        {1,2,4,5,3},                             // connect two intervals into one
        {100,101,102,101,100,102},               // insert within existing interval and duplicates
        {0,0,1000,1000,-1,-1,1,1},               // scattered with duplicates
        {2,4,6,8,10,12},                         // multiple non-overlapping singles
        {50,52,54,53,51,55,49,48,47}             // merges into a large interval in mixed order
    };

    volatile long long checksum = 0; // volatile to help prevent optimization

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& seq : tests) {
            SummaryRanges sr;
            size_t half = seq.size() / 2;
            for (size_t i = 0; i < seq.size(); ++i) {
                sr.addNum(seq[i]);
                if (i == half) {
                    auto ivs_mid = sr.getIntervals();
                    checksum += static_cast<long long>(ivs_mid.size());
                    if (!ivs_mid.empty()) {
                        checksum += (static_cast<long long>(ivs_mid.front()[0]) ^ static_cast<long long>(ivs_mid.back()[1]));
                    }
                }
            }
            auto ivs = sr.getIntervals();
            for (const auto& iv : ivs) {
                checksum += ((static_cast<long long>(iv[0]) * 1315423911LL) ^ static_cast<long long>(iv[1]));
            }
            checksum += static_cast<long long>(ivs.size());
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}