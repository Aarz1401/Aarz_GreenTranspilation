#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <functional>
#include <utility>
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
                if (it != unordered_map<long long, int>::iterator{}) {
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
                if (it != unordered_map<long long, int>::iterator{}) {
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

struct Test {
    vector<int> nums;
    int k;
};

int main() {
    vector<Test> tests = {
        {{1, 3, -1, -3, 5, 3, 6, 7}, 3},
        {{1, 3, -1, -3, 5, 3, 6, 7}, 4},
        {{5}, 1},
        {{2, 2, 2, 2, 2, 2}, 3},
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5},
        {{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 2},
        {{0, -1, 1, 0, -2, 2, 0, -3, 3, 0}, 7},
        {{100, -100, 50, -50, 25, -25, 75, -75, 0, 0}, 4},
        {{500, -200, 300, -400, 1000, -1000, 750, -750, 250, -250, 125, -125, 60, -60, 30, -30, 15, -15, 7, -7}, 10},
        {{4, 1, 7, 8, 5, 2, 6, 3, 9}, 9}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            auto nums = t.nums;
            int k = t.k;
            auto res = sol.medianSlidingWindow(nums, k);
            checksum += static_cast<int>(res.size());
            for (double v : res) {
                checksum += static_cast<int>(v);
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}