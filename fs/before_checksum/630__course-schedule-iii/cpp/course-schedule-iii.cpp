#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Time:  O(nlogn)
// Space: O(k), k is the number of courses you can take
class Solution {
public:
    int scheduleCourse(vector<vector<int>>& courses) {
        sort(courses.begin(), courses.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });
        priority_queue<int> max_heap;
        long long now = 0;
        for (const auto& c : courses) {
            int t = c[0], end = c[1];
            now += t;
            max_heap.push(t);
            if (now > end) {
                now -= max_heap.top();
                max_heap.pop();
            }
        }
        return static_cast<int>(max_heap.size());
    }
};