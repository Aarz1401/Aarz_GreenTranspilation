#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <algorithm>
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

volatile int sink = 0;

int main() {
    Solution sol;
    vector<vector<vector<int>>> tests = {
        {{1,1}},
        {{5,4},{6,4},{6,7},{2,3}},
        {{1,10},{1,9},{1,8},{1,7}},
        {{4,5},{4,6},{6,7},{2,3},{1,1},{7,8}},
        {{8,9},{5,6},{6,7},{2,3},{3,4}},
        {{2,100},{3,200},{4,300},{5,500},{5,400},{5,250},{6,370},{6,360},{7,380}},
        {{10,10},{9,9},{8,8},{7,7},{6,6}},
        {{1,2},{2,2},{3,2},{4,2}},
        {{10000,10000},{9999,10001},{10001,9999},{10002,10002}},
        {{2,2},{3,3},{3,2},{4,3},{5,5},{5,4},{6,7},{7,6}}
    };

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            auto input = t;
            int r = sol.maxEnvelopes(input);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }
    return 0;
}