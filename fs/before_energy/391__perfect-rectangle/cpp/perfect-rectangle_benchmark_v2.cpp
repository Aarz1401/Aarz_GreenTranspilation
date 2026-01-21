#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <unordered_map>
#include <limits>
#include <cstdint>
#include <algorithm>
using namespace std;

// Time:  O(n)
// Space: O(n)

class Solution {
public:
    bool isRectangleCover(vector<vector<int>>& rectangles) {
        int left = numeric_limits<int>::max();
        int bottom = numeric_limits<int>::max();
        int right = numeric_limits<int>::min();
        int top = numeric_limits<int>::min();

        auto key = [](int x, int y) -> long long {
            return (static_cast<long long>(x) << 32) | static_cast<unsigned int>(y);
        };

        unordered_map<long long, int> points;

        for (const auto& rec : rectangles) {
            int l = rec[0], b = rec[1], r = rec[2], t = rec[3];
            left = min(left, l);
            bottom = min(bottom, b);
            right = max(right, r);
            top = max(top, t);

            const int masks[4] = {1, 2, 4, 8};
            const int xs[4] = {l, r, l, r};
            const int ys[4] = {b, b, t, t};

            for (int i = 0; i < 4; ++i) {
                long long k = key(xs[i], ys[i]);
                int q = masks[i];
                int& cur = points[k];
                if (cur & q) {
                    return false;
                }
                cur |= q;
            }
        }

        for (const auto& kv : points) {
            long long k = kv.first;
            int mask = kv.second;
            int px = static_cast<int>(k >> 32);
            int py = static_cast<int>(static_cast<uint32_t>(k));
            if ((left < px && px < right) || (bottom < py && py < top)) {
                if (!(mask == 3 || mask == 5 || mask == 10 || mask == 12 || mask == 15)) {
                    return false;
                }
            }
        }

        return true;
    }
};

int main() {
    vector<vector<vector<int>>> tests = {
        // 1) Single rectangle (true)
        { {0, 0, 2, 3} },
        // 2) 2x2 covered by four 1x1 tiles (true)
        { {0,0,1,1}, {1,0,2,1}, {0,1,1,2}, {1,1,2,2} },
        // 3) Overlapping rectangles (false)
        { {0,0,2,2}, {1,1,3,3} },
        // 4) Gap: three of the four tiles (false)
        { {0,0,1,1}, {1,0,2,1}, {0,1,1,2} },
        // 5) Duplicate rectangle (false)
        { {0,0,1,1}, {0,0,1,1} },
        // 6) Mixed tiling covering [0,0,3,2] (true)
        { {0,0,1,2}, {1,0,2,1}, {1,1,2,2}, {2,0,3,2} },
        // 7) Negative coordinates perfect cover [-3,-1,2,3] (true)
        { {-3,-1,-1,3}, {-1,-1,2,1}, {-1,1,2,3} },
        // 8) Large coordinates within typical constraints (true)
        { {10000,10000,15000,15000}, {15000,10000,20000,15000},
          {10000,15000,15000,20000}, {15000,15000,20000,20000} },
        // 9) Another perfect cover [0,0,4,3] (true)
        { {0,0,1,3}, {1,0,4,1}, {1,1,4,3} },
        // 10) Gap near edge in [0,0,3,2] (false)
        { {0,0,2,2}, {2,0,3,1} }
    };

    Solution sol;

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& recs : tests) {
            int r = sol.isRectangleCover(recs);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }
    return 0;
}