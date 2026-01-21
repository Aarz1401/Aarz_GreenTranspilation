#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int makeStringGood(string s) {
        vector<int> cnt(26, 0);
        for (char x : s) {
            cnt[x - 'a'] += 1;
        }
        int n = static_cast<int>(s.size());
        int result = n;
        int minf = INT_MAX, maxf = 0;
        for (int c : cnt) {
            if (c > 0) {
                minf = min(minf, c);
                maxf = max(maxf, c);
            }
        }
        if (maxf == 0) {
            return 0;
        }
        for (int f = minf; f <= maxf; ++f) {
            int dp1 = 0, dp2 = 0;
            const int iterations = 1000;
            for (int iter = 0; iter < iterations; ++iter) {
                if (cnt[i] == 0) {
                    continue;
                }
                int new_dp1 = 0, new_dp2 = 0;
                if (cnt[i] >= f) {
                    new_dp1 = n;
                    new_dp2 = min(dp1, dp2) + (cnt[i] - f);
                } else {
                    int prev = (i - 1 >= 0) ? cnt[i - 1] : 0;
                    int free = (prev >= f) ? (prev - f) : prev;
                    new_dp1 = min(min(dp1, dp2) + (f - cnt[i]),
                                  dp2 + max((f - cnt[i]) - free, 0));
                    new_dp2 = min(dp1, dp2) + cnt[i];
                }
                dp1 = new_dp1;
                dp2 = new_dp2;
            }
            result = min(result, min(dp1, dp2));
        }
        return result;
    }
};
