#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <utility>
using namespace std;

class Solution {
public:
    int minimumIncrements(vector<int>& nums, vector<int>& target) {
        using int64 = long long;
        const int64 INF = LLONG_MAX / 4;

        auto gcdll = [&](int64 a, int64 b) {
            while (b) {
                int64 t = a % b;
                a = b;
                b = t;
            }
            return a;
        };

        auto lcm_saturate = [&](int64 a, int64 b) {
            if (a == 0 || b == 0) return 0LL;
            int64 g = gcdll(a, b);
            int64 t = a / g;
            if (t > INF / b) return INF;
            return t * b;
        };

        int n = nums.size();
        int m = target.size();
        int total = 1 << m;

        vector<int64> lcms(total, 1);
        for (int mask = 0; mask < total; ++mask) {
            int64 l = 1;
            for (int i = 0; i < m; ++i) {
                if (mask & (1 << i)) {
                    l = lcm_saturate(l, static_cast<int64>(target[i]));
                    if (l >= INF) { l = INF; break; }
                }
            }
            lcms[mask] = l;
        }

        vector<int64> dp(total, INF);
        dp[0] = 0;

        for (int x : nums) {
            for (int mask = total - 1; mask >= 0; --mask) {
                if (dp[mask] == INF) continue;
                int new_mask = (total - 1) ^ mask;
                int submask = new_mask;
                while (submask) {
                    int64 l = lcms[submask];
                    int64 rem = l == 0 ? 0 : (static_cast<int64>(x) % l);
                    int64 inc = (rem == 0) ? 0 : (l - rem);
                    dp[mask | submask] = min(dp[mask | submask], dp[mask] + inc);
                    submask = (submask - 1) & new_mask;
                }
            }
        }

        return static_cast<int>(dp[total - 1]);
    }
};

int main() {
    vector<pair<vector<int>, vector<int>>> tests = {
        { {2}, {2} },
        { {1,3}, {2,3} },
        { {4,9}, {2,3,4} },
        { {5,6}, {4,9} },
        { {10,14,20}, {7} },
        { {1,2}, {2,2,3} },
        { {8,9,10}, {2,5,3} },
        { {6,10,15,30}, {2,3,5} },
        { {2147483647, 2147483629}, {2147483647, 2147483629} },
        { {1,2,3,4,5}, {2,3,4,5,6,7,8,9} }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;

        for (auto& t : tests) {
            checksum += sol.minimumIncrements(t.first, t.second);
        }

        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}