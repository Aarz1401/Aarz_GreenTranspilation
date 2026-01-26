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

struct Op { int t, l, r; };

int main() {
    vector<vector<Op>> tests = {
        {
            {0, 5, 10}, {2, 6, 9}, {2, 4, 6}, {0, 8, 12},
            {2, 10, 12}, {1, 7, 9}, {2, 7, 9}, {2, 5, 7}
        },
        {
            {0, 1, 3}, {0, 3, 5}, {2, 2, 4}, {2, 1, 5},
            {1, 2, 3}, {2, 2, 3}, {2, 1, 2}
        },
        {
            {0, 10, 20}, {0, 30, 40}, {2, 15, 35}, {2, 30, 40},
            {1, 35, 37}, {2, 36, 37}, {0, 35, 37}, {2, 32, 38}
        },
        {
            {0, 1, 2}, {1, 1, 2}, {2, 1, 2}, {0, 1, 6},
            {2, 1, 6}, {1, 2, 5}, {2, 1, 2}, {2, 5, 6}, {2, 2, 5}
        },
        {
            {0, 100000000, 200000000}, {0, 150000000, 250000000},
            {1, 120000000, 130000000}, {2, 110000000, 115000000},
            {2, 120000000, 130000000}, {2, 200000000, 250000000}
        },
        {
            {0, 1, 2}, {0, 2, 3}, {0, 3, 4}, {0, 4, 5},
            {1, 2, 4}, {0, 2, 4}, {2, 1, 5}, {2, 1, 6}, {1, 1, 5}, {2, 1, 2}
        },
        {
            {0, 10, 15}, {0, 12, 14}, {2, 11, 13}, {1, 13, 14},
            {2, 13, 14}, {0, 13, 14}, {2, 10, 15}
        },
        {
            {0, 50, 60}, {1, 40, 45}, {2, 50, 60}, {1, 55, 65},
            {2, 55, 60}, {2, 50, 55}
        },
        {
            {0, 5, 7}, {0, 20, 25}, {0, 8, 10}, {0, 7, 8},
            {2, 6, 9}, {1, 6, 9}, {2, 5, 6}, {2, 6, 9}, {2, 9, 10},
            {0, 15, 18}, {2, 15, 20}, {0, 10, 15}, {2, 12, 17},
            {1, 17, 22}, {2, 21, 23}, {2, 22, 23}
        },
        {
            {0, 1, 3}, {0, 3, 5}, {0, 7, 9}, {2, 5, 7},
            {0, 5, 7}, {1, 4, 8}, {2, 1, 4}, {2, 4, 8}, {2, 8, 9}
        }
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& test : tests) {
            RangeModule rm;
            for (const auto& op : test) {
                if (op.t == 0) {
                    rm.addRange(op.l, op.r);
                } else if (op.t == 1) {
                    rm.removeRange(op.l, op.r);
                } else if (op.t == 2) {
                    int r = rm.queryRange(op.l, op.r);
                    DoNotOptimize(r);
                }
            }
        }
        //sink = checksum;
    }
    return 0;
}