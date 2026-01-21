#include <algorithm>
#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>

using namespace std;

// Time:  O(nlogn)
// Space: O(1)
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // Sort by width asc; if same width, height desc
        sort(envelopes.begin(), envelopes.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] == b[0]) return a[1] > b[1];
                 return a[0] < b[0];
             });

        vector<int> result;
        for (const auto& envelope : envelopes) {
            insert(result, envelope[1]);
        }
        return static_cast<int>(result.size());
    }

private:
    void insert(vector<int>& result, int target) {
        auto it = lower_bound(result.begin(), result.end(), target);
        if (it == result.end()) {
            result.emplace_back(target);
        } else {
            *it = target;
        }
    }
};