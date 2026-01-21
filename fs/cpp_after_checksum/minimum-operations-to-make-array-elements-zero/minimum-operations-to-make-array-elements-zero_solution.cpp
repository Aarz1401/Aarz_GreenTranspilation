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

// Time:  O(qlogr)
// Space: O(1)

// greedy
class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        long long result = 0;
        for (const auto& q : queries) {
            long long l = q[0], r = q[1];
            __int128 total = 0;
            long long base = 1;
            long long i = 1;
            while (base <= r) {
                long long nl = max(l, base);
                __int128 hi128 = (__int128)4 * base - 1;
                long long hi = hi128 > LLONG_MAX ? LLONG_MAX : (long long)hi128;
                long long nr = min(r, hi);
                if (nl <= nr) {
                    total += (__int128)i * (nr - nl + 1);
                }
                ++i;
                if (base > LLONG_MAX / 4) {
                    break;
                }
                base *= 4;
            }
            result += (long long)((total + 1) / 2);
        }
        return result;
    }
};
