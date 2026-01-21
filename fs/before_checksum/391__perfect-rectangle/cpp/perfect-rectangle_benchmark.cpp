#include <iostream>
#include <vector>
#include <unordered_map>
#include <limits>
#include <cstdint>
#include <algorithm>
#include <chrono>

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
    // Define 10 diverse test inputs
    vector<vector<vector<int>>> tests;

    // 0: Two rectangles forming a perfect 2x2 rectangle vertically
    tests.push_back({
        {1, 1, 3, 2},
        {1, 2, 3, 3}
    });

    // 1: Complex valid tiling (LeetCode-style valid example)
    tests.push_back({
        {1,1,3,3},
        {3,1,4,2},
        {3,2,4,4},
        {1,3,2,4},
        {2,3,3,4},
        {1,1,2,2},
        {2,2,3,3},
        {1,2,2,3},
        {2,1,3,2}
    });

    // 2: Overlapping rectangles (invalid)
    tests.push_back({
        {1,1,2,3},
        {1,3,2,4},
        {3,1,4,2},
        {2,2,4,4}
    });

    // 3: Hole in the middle (invalid)
    tests.push_back({
        {1,1,3,3},
        {3,1,4,2},
        {3,2,4,4},
        {1,3,2,4},
        {2,3,3,4},
        {1,1,2,2},
        {1,2,2,3},
        {2,1,3,2}
    });

    // 4: Four rectangles forming a 2x2 square (valid)
    tests.push_back({
        {0,0,1,1},
        {1,0,2,1},
        {0,1,1,2},
        {1,1,2,2}
    });

    // 5: Single rectangle (valid)
    tests.push_back({
        {5,5,10,10}
    });

    // 6: Duplicate identical rectangles (invalid)
    tests.push_back({
        {0,0,1,1},
        {0,0,1,1}
    });

    // 7: Negative coordinates, two rectangles side-by-side (valid)
    tests.push_back({
        {-3,-1,-1,1},
        {-1,-1,1,1}
    });

    // 8: Disjoint rectangles (likely invalid)
    tests.push_back({
        {0,0,1,1},
        {2,0,3,1}
    });

    // 9: Large coordinates tiling a big rectangle with 10 vertical stripes (valid)
    {
        vector<vector<int>> big;
        int x0 = 100000000;
        int y0 = 200000000;
        for (int i = 0; i < 10; ++i) {
            big.push_back({x0 + i, y0, x0 + i + 1, y0 + 5});
        }
        tests.push_back(big);
    }

    Solution sol;
    uint64_t checksum = 0;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run all test cases
        for (size_t i = 0; i < tests.size(); ++i) {
            bool res = sol.isRectangleCover(tests[i]);
            // Mix into checksum to prevent optimization
            checksum = (checksum * 1315423911ull) ^ static_cast<uint64_t>(res + i + tests[i].size());
        }
    }

    auto end = clock::now();
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << ns << "\n";
    return 0;
}