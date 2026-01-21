#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

int main() {
    vector<vector<vector<int>>> tests = {
        { {1, 1} },
        { {4, 4} },
        { {2, 5} },
        { {1, 16} },
        { {1, 3}, {4, 7}, {8, 15} },
        { {10, 100} },
        { {5, 5}, {6, 20}, {21, 64} },
        { {1, 1000000} },
        { {2147483600, 2147483647} },
        { {123456, 123789}, {999999, 1000010} }
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& qs : tests) {
            long long res = sol.minOperations(qs);
            DoNotOptimize(res); 
            //checksum += static_cast<int>(res);
        }
        //sink = checksum;
    }
    return 0;
}