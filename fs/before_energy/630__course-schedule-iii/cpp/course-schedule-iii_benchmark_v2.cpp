#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

volatile int sink = 0;

int main() {
    vector<vector<vector<int>>> tests = {
        {{100,200},{200,1300},{1000,1250},{2000,3200}},
        {{1,2},{2,3},{3,4}},
        {{5,5},{4,6},{2,6}},
        {{5,4},{6,5},{7,6}},
        {{1,1},{1,2},{1,3},{1,4},{1,5},{1,6},{1,7},{1,8},{1,9},{1,10}},
        {{1000,1000},{1000,2000},{1000,3000},{1000,4000},{1000,5000}},
        {{5,5},{4,5},{3,5},{2,5},{1,5}},
        {{2,2}},
        {{3,3},{2,2},{1,1},{4,4}},
        {{7,17},{3,12},{10,20},{9,19},{12,25},{8,29},{6,18}}
    };

    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& tc : tests) {
            int r = sol.scheduleCourse(tc);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}