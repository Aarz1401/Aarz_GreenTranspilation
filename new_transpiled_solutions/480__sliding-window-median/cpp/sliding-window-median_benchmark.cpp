#include <chrono>
#include <climits>
#include <iostream>
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

int main() {
    // Prepare 10 diverse test inputs
    struct TestCase {
        vector<int> nums;
        int k;
    };

    vector<TestCase> tests;

    // 1. Classic mixed example, odd k
    tests.push_back(TestCase{{1, 3, -1, -3, 5, 3, 6, 7}, 3});

    // 2. Single element, k = 1
    tests.push_back(TestCase{{42}, 1});

    // 3. Small ascending, even k
    tests.push_back(TestCase{{1, 2, 3, 4, 5}, 2});

    // 4. Descending, even k
    tests.push_back(TestCase{{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4});

    // 5. All duplicates, odd k
    tests.push_back(TestCase{{5, 5, 5, 5, 5, 5, 5}, 5});

    // 6. Negatives and positives, odd k
    tests.push_back(TestCase{{-10, -5, 0, 5, 10, -15, 20, 25, -30}, 5});

    // 7. Extreme integer values, odd k
    tests.push_back(TestCase{{INT_MAX, INT_MIN, INT_MAX - 1, INT_MIN + 1, 0, 123456789, -123456789}, 3});

    // 8. Empty input with k = 0
    tests.push_back(TestCase{{}, 0});

    // 9. Larger dataset with patterned values, k = 50
    {
        vector<int> v;
        v.reserve(200);
        for (int i = 0; i < 200; ++i) {
            int val = ((i * 37) % 100) - 50 + ((i & 1) ? i : -(i / 2));
            v.push_back(val);
        }
        tests.push_back(TestCase{std::move(v), 50});
    }

    // 10. Window size equals array size
    {
        vector<int> v;
        v.reserve(30);
        for (int i = 0; i < 30; ++i) {
            int val = ((i % 2) ? i : -i) + ((i % 5 == 0) ? 3 : -3);
            v.push_back(val);
        }
        tests.push_back(TestCase{std::move(v), 30});
    }

    Solution sol;
    volatile double checksum = 0.0; // volatile to prevent optimization of the accumulation

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            vector<double> res = sol.medianSlidingWindow(tests[t].nums, tests[t].k);
            // Accumulate a checksum based on results and indices
            for (size_t i = 0; i < res.size(); ++i) {
                checksum += res[i] * (1.0 + static_cast<double>(i + t));
            }
            checksum += static_cast<double>(res.size() + tests[t].k);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}