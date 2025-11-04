#include <algorithm>
#include <array>
#include <climits>
#include <cmath>
#include <cstdint>
#include <deque>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

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