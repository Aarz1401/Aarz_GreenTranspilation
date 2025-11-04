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