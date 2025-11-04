#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;

// Time:  O(nlogn) for total n addNums, O(logn) per addNum, O(1) per findMedian.
// Space: O(n), total space

class MedianFinder {
public:
    MedianFinder() {}

    // Adds a num into the data structure.
    void addNum(int num) {
        // Balance smaller half and larger half.
        if (max_heap.empty() || num > max_heap.top()) {
            min_heap.push(num);
            if (min_heap.size() > max_heap.size() + 1) {
                max_heap.push(min_heap.top());
                min_heap.pop();
            }
        } else {
            max_heap.push(num);
            if (max_heap.size() > min_heap.size()) {
                min_heap.push(max_heap.top());
                max_heap.pop();
            }
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        return (min_heap.size() == max_heap.size())
                   ? (max_heap.top() + min_heap.top()) / 2.0
                   : static_cast<double>(min_heap.top());
    }

private:
    priority_queue<int> max_heap; // stores the smaller half
    priority_queue<int, vector<int>, greater<int>> min_heap; // stores the larger half
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Prepare 10 diverse test inputs
    vector<vector<int>> tests;
    tests.reserve(10);

    // 1) Increasing sequence 1..100
    {
        vector<int> v;
        for (int i = 1; i <= 100; ++i) v.push_back(i);
        tests.push_back(move(v));
    }

    // 2) Decreasing sequence 100..1
    {
        vector<int> v;
        for (int i = 100; i >= 1; --i) v.push_back(i);
        tests.push_back(move(v));
    }

    // 3) All zeros (100 elements)
    {
        vector<int> v(100, 0);
        tests.push_back(move(v));
    }

    // 4) Alternating -1 and 1 (200 elements)
    {
        vector<int> v;
        v.reserve(200);
        for (int i = 0; i < 200; ++i) v.push_back((i % 2 == 0) ? -1 : 1);
        tests.push_back(move(v));
    }

    // 5) Range -50..50 (101 elements)
    {
        vector<int> v;
        for (int i = -50; i <= 50; ++i) v.push_back(i);
        tests.push_back(move(v));
    }

    // 6) Predefined mixed values
    {
        vector<int> v = {5, 3, 8, 9, 1, 4, 7, 2, 6, 0, -3, 12, -7, 15, -1, 13, -5, 11, 14, -2,
                         100, -50, 25, -25, 75, -60, 33, -33, 88, -88};
        tests.push_back(move(v));
    }

    // 7) Symmetric large magnitudes around zero (200 elements): safe sums
    {
        vector<int> v;
        v.reserve(200);
        for (int k = 0; k < 100; ++k) {
            v.push_back(-1000000 + k);
            v.push_back( 1000000 - k);
        }
        tests.push_back(move(v));
    }

    // 8) Single element
    {
        vector<int> v = {7};
        tests.push_back(move(v));
    }

    // 9) Two elements (even count)
    {
        vector<int> v = {5, 10};
        tests.push_back(move(v));
    }

    // 10) Zigzag sequence
    {
        vector<int> v = {10, -10, 20, -20, 30, -30, 40, -40, 50, -50,
                         60, -60, 70, -70, 80, -80, 90, -90, 100, -100};
        tests.push_back(move(v));
    }

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::microseconds;

    double checksum = 0.0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            MedianFinder mf;
            double local_acc = 0.0;
            const vector<int>& arr = tests[t];
            for (size_t i = 0; i < arr.size(); ++i) {
                mf.addNum(arr[i]);
                // Occasionally query to ensure work is observable
                if ((i & 7) == 0) {
                    local_acc += mf.findMedian();
                }
            }
            local_acc += mf.findMedian();
            checksum += local_acc;
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << fixed << setprecision(6);
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed (microseconds): " << elapsed_us << "\n";
    return 0;
}