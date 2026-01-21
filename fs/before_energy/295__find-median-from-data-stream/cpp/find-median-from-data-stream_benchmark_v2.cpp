#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <queue>
#include <vector>
#include <functional>

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
    vector<vector<int>> tests = {
        {1},
        {1, 2},
        {2, 1, 5, 7, 2, 0, 5},
        {-5, -10, -3, -4, -1},
        {100, 100, 100, 100, 100},
        {5, 4, 3, 2, 1, 0},
        {0, -1, 1, -2, 2, -3, 3},
        {10, 20, 30, 40, 50, 60, 70, 80},
        {3, 3, 4, 2, 2, 1, 5, 5, 6},
        {7, 0, 0, 7, -7, 14, -14, 7, -7, 0}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            MedianFinder mf;
            for (int x : t) {
                mf.addNum(x);
            }
            int r = static_cast<int>(mf.findMedian());
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }
    return 0;
}