#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <utility>
#include <algorithm>
#include <limits>

using namespace std;

// Time:  addRange:    O(n)
//        removeRange: O(n)
//        queryRange:  O(logn)
// Space: O(n)

class RangeModule {
public:
    RangeModule() {}

    void addRange(int left, int right) {
        vector<pair<int, int>> tmp;
        size_t i = 0;
        for (const auto& interval : intervals_) {
            if (right < interval.first) {
                tmp.emplace_back(left, right);
                break;
            } else if (interval.second < left) {
                tmp.emplace_back(interval);
            } else {
                left = min(left, interval.first);
                right = max(right, interval.second);
            }
            ++i;
        }
        if (i == intervals_.size()) {
            tmp.emplace_back(left, right);
        }
        while (i < intervals_.size()) {
            tmp.emplace_back(intervals_[i]);
            ++i;
        }
        intervals_.swap(tmp);
    }

    bool queryRange(int left, int right) {
        auto it = lower_bound(intervals_.begin(), intervals_.end(),
                              make_pair(left, numeric_limits<int>::max()));
        size_t i = static_cast<size_t>(it - intervals_.begin());
        if (!intervals_.empty() && i > 0) {
            --i;
        }
        return !intervals_.empty() &&
               intervals_[i].first <= left &&
               right <= intervals_[i].second;
    }

    void removeRange(int left, int right) {
        vector<pair<int, int>> tmp;
        for (const auto& interval : intervals_) {
            if (interval.second <= left || interval.first >= right) {
                tmp.emplace_back(interval);
            } else {
                if (interval.first < left) {
                    tmp.emplace_back(interval.first, left);
                }
                if (right < interval.second) {
                    tmp.emplace_back(right, interval.second);
                }
            }
        }
        intervals_.swap(tmp);
    }

private:
    vector<pair<int, int>> intervals_;
};