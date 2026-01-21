#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <limits>
#include <utility>
#include <chrono>

using namespace std;

// Time:  O(n^2), could be improved to O(nlogn) in cpp by ordered map (bst)
// Space: O(n)
class Solution {
public:
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        vector<int> result;
        vector<int> pos = {-1};
        vector<int> heights = {0};
        int maxH = 0;
        for (const auto& p : positions) {
            int left = p[0];
            int side = p[1];

            int l = static_cast<int>(upper_bound(pos.begin(), pos.end(), left) - pos.begin());
            int r = static_cast<int>(lower_bound(pos.begin(), pos.end(), left + side) - pos.begin());

            int highBase = 0;
            int start = l - 1;
            int end = r - 1;
            if (start <= end) {
                for (int i = start; i <= end; ++i) {
                    highBase = max(highBase, heights[i]);
                }
            }
            int high = highBase + side;

            int rightHeight = heights[r - 1];

            pos.erase(pos.begin() + l, pos.begin() + r);
            pos.insert(pos.begin() + l, left + side);
            pos.insert(pos.begin() + l, left);

            heights.erase(heights.begin() + l, heights.begin() + r);
            heights.insert(heights.begin() + l, rightHeight);
            heights.insert(heights.begin() + l, high);

            maxH = max(maxH, high);
            result.push_back(maxH);
        }
        return result;
    }
};

int main() {
    // Define 10 diverse test inputs
    vector<vector<vector<int>>> tests;
    tests.reserve(10);

    // 1) Basic overlapping and non-overlapping
    tests.push_back({{1,2},{2,3},{6,1}});

    // 2) Non-overlapping sequence
    tests.push_back({{0,1},{2,1},{4,1},{6,1},{8,1},{10,1}});

    // 3) Same position, increasing sizes
    tests.push_back({{0,100},{0,1},{0,2},{0,3},{0,4}});

    // 4) Chain overlaps
    tests.push_back({{0,2},{1,2},{2,2},{3,2},{4,2},{5,2},{6,2},{7,2}});

    // 5) Nested intervals and extensions
    tests.push_back({{1,5},{2,3},{3,1},{2,5},{1,2},{0,6}});

    // 6) Large coordinates, safe sums
    tests.push_back({{1000000000 - 100, 50},{1000000000 - 150, 75},{500000000, 100},{1000000000 - 200, 60}});

    // 7) Mixed random-like pattern
    tests.push_back({{5,4},{13,2},{2,3},{11,5},{7,1},{6,4},{15,2},{14,3}});

    // 8) Back-and-forth placements
    tests.push_back({{10,3},{7,2},{12,4},{9,1},{8,5},{11,2},{6,3}});

    // 9) Sparse grid of identical sizes
    {
        vector<vector<int>> t9;
        for (int i = 0; i < 20; ++i) {
            t9.push_back({i * 3, 2});
        }
        tests.push_back(std::move(t9));
    }

    // 10) Heavier test: 60 items with alternating overlaps and varying sizes
    {
        vector<vector<int>> t10;
        t10.reserve(60);
        for (int i = 0; i < 60; ++i) {
            int left = i - (i % 3 == 0 ? 0 : 1); // cause overlaps frequently
            int side = (i % 7) + 1;              // sizes 1..7
            t10.push_back({left, side});
        }
        tests.push_back(std::move(t10));
    }

    Solution sol;
    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::microseconds;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<int> res = sol.fallingSquares(tests[i]);
            for (int v : res) checksum += v;
            checksum ^= static_cast<long long>(res.size() * (i + 1));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}