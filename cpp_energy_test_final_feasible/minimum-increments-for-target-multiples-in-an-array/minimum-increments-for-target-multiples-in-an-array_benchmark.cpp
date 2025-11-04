#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>
#include <cstdint>
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
    // Define 10 diverse test inputs
    vector<pair<vector<int>, vector<int>>> testcases;

    // 1. Simple case
    testcases.push_back({{5}, {2}});

    // 2. Duplicated targets, zero in nums
    testcases.push_back({{0}, {1, 1}});

    // 3. Small arrays
    testcases.push_back({{1, 2}, {3}});

    // 4. Empty target
    testcases.push_back({{7}, {}});

    // 5. Exact multiples already for one, needs increment for another
    testcases.push_back({{4, 8}, {4}});

    // 6. Two targets, coprime-ish
    testcases.push_back({{9}, {6, 10}});

    // 7. Zero in target
    testcases.push_back({{1}, {0}});

    // 8. Large values to exercise saturation behavior
    testcases.push_back({{1000000000}, {2000000000, 1999999999}});

    // 9. Mixed zero and non-zero in target
    testcases.push_back({{5}, {5, 0}});

    // 10. Three targets
    testcases.push_back({{2}, {4, 6, 8}});

    Solution sol;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    uint64_t checksum = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < testcases.size(); ++i) {
            auto& nums = testcases[i].first;
            auto& target = testcases[i].second;
            int res = sol.minimumIncrements(nums, target);
            // Combine result into checksum to prevent optimization
            checksum ^= (static_cast<uint64_t>(res) + 0x9e3779b97f4a7c15ULL + (i << 1) + (static_cast<uint64_t>(iter) & 0xFF));
            // Mask to keep it in 64 bits reliably across compilers
            checksum = (checksum << 1) | (checksum >> 63);
        }
    }

    auto end = high_resolution_clock::now();
    auto ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Time (ns): " << ns << "\n";

    return 0;
}