#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <cstdint>
using namespace std;

// Time:  O(nlogk)
// Space: O(k)
class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> result;
        if (k == 0 || nums.empty()) return result;

        priority_queue<long long> lo; // max-heap for lower half
        priority_queue<long long, vector<long long>, greater<long long>> hi; // min-heap for upper half
        unordered_map<long long, int> delayed; // lazy deletion map

        int loSize = 0; // valid elements in lo
        int hiSize = 0; // valid elements in hi

        auto pruneLo = [&]() {
            while (!lo.empty()) {
                long long x = lo.top();
                auto it = delayed.find(x);
                if (it != delayed.end()) {
                    if (--(it->second) == 0) delayed.erase(it);
                    lo.pop();
                } else {
                    break;
                }
            }
        };

        auto pruneHi = [&]() {
            while (!hi.empty()) {
                long long x = hi.top();
                auto it = delayed.find(x);
                if (it != delayed.end()) {
                    if (--(it->second) == 0) delayed.erase(it);
                    hi.pop();
                } else {
                    break;
                }
            }
        };

        auto balance = [&]() {
            // Ensure hi has the same number of elements as lo, or one more.
            if (loSize > hiSize) {
                hi.push(lo.top());
                lo.pop();
                loSize--;
                hiSize++;
                pruneLo();
            } else if (hiSize > loSize + 1) {
                lo.push(hi.top());
                hi.pop();
                hiSize--;
                loSize++;
                pruneHi();
            }
        };

        auto addNum = [&](long long num) {
            if (!hi.empty() && num >= hi.top()) {
                hi.push(num);
                hiSize++;
            } else {
                lo.push(num);
                loSize++;
            }
            balance();
        };

        auto removeNum = [&](long long num) {
            delayed[num]++;
            if (!hi.empty() && num >= hi.top()) {
                hiSize--;
                if (!hi.empty() && num == hi.top()) {
                    pruneHi();
                }
            } else {
                loSize--;
                if (!lo.empty() && num == lo.top()) {
                    pruneLo();
                }
            }
            balance();
        };

        auto getMedian = [&]() -> double {
            if (k % 2 == 1) {
                return static_cast<double>(hi.top());
            } else {
                return (static_cast<double>(hi.top()) + static_cast<double>(lo.top())) / 2.0;
            }
        };

        // Build initial window
        for (int i = 0; i < k; ++i) {
            addNum(static_cast<long long>(nums[i]));
        }
        result.push_back(getMedian());

        // Slide the window
        for (int i = k; i < static_cast<int>(nums.size()); ++i) {
            addNum(static_cast<long long>(nums[i]));
            removeNum(static_cast<long long>(nums[i - k]));
            result.push_back(getMedian());
        }

        return result;
    }
};