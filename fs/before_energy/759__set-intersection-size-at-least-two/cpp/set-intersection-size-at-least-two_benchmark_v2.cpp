#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <cstddef>
using namespace std;

// Time:  O(nlogn)
// Space: O(n)

class Solution {
public:
    int intersectionSizeTwo(vector<vector<int>>& intervals) {
        // intervals.sort(key = lambda s_e: (s_e[0], -s_e[1]))
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] != b[0]) return a[0] < b[0];
                 return a[1] > b[1];
             });

        vector<int> cnts(intervals.size(), 2);
        int result = 0;

        while (!intervals.empty()) {
            int start = intervals.back()[0];
            int cnt = cnts.back();
            intervals.pop_back();
            cnts.pop_back();

            for (int s = start; s < start + cnt; ++s) {
                for (size_t i = 0; i < intervals.size(); ++i) {
                    if (cnts[i] > 0 && s <= intervals[i][1]) {
                        cnts[i] -= 1;
                    }
                }
            }
            result += cnt;
        }
        return result;
    }
};

volatile int sink = 0;

int main() {
    vector<vector<vector<int>>> tests = {
        {{1,3},{1,4},{2,5},{3,5}},
        {{1,2},{4,5},{7,8}},
        {{0,10},{0,9},{1,8},{2,7},{3,6},{4,5}},
        {{5,10}},
        {{1,2},{2,3},{3,4},{4,5}},
        {{10,20},{15,25},{18,22},{21,30},{5,12},{0,3}},
        {{1000000,1000002},{999998,1000001},{500000,700000}},
        {{2,6},{2,7},{2,8},{3,9},{0,5}},
        {{0,1},{1,2},{2,3},{3,4},{4,6},{5,7},{6,8}},
        {{8,10},{1,3},{2,5},{6,9},{4,7},{0,2}}
    };

    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            vector<vector<int>> in = t;
            int r = sol.intersectionSizeTwo(in);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}