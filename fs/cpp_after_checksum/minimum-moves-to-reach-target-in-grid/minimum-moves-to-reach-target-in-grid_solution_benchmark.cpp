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

class Solution {
public:
    int minMoves(int sx, int sy, int tx, int ty) {
        long long lsx = sx, lsy = sy, ltx = tx, lty = ty;
        long long result = 0;
        while (!(lsx == ltx && lsy == lty)) {
            if (!(lsx <= ltx && lsy <= lty)) {
                return -1;
            }
            if (ltx < lty) {
                if (ltx > lty - ltx) {
                    lty -= ltx;
                } else {
                    if (lty % 2) {
                        return -1;
                    }
                    lty -= lty / 2;
                }
            } else if (ltx > lty) {
                if (lty > ltx - lty) {
                    ltx -= lty;
                } else {
                    if (ltx % 2) {
                        return -1;
                    }
                    ltx -= ltx / 2;
                }
            } else {
                if (lsx == 0) {
                    ltx -= lty;
                } else if (lsy == 0) {
                    lty -= ltx;
                } else {
                    return -1;
                }
            }
            ++result;
        }
        return static_cast<int>(result);
    }
};

struct TestCase {
    int sx, sy, tx, ty;
};

int main() {
    Solution sol;

    vector<TestCase> tests = {
        {5, 7, 5, 7},                 // already at target
        {0, 1, 4, 4},                 // reachable via sx == 0 path
        {3, 0, 12, 12},               // reachable via sy == 0 path
        {5, 2, 4, 5},                 // unreachable: source > target in x
        {1, 1, 2, 3},                 // likely unreachable due to parity/equality constraints
        {0, 2, 32, 32},               // reachable via halving y to source
        {8, 0, 32, 32},               // reachable via halving x to source
        {1, 2, 1000000, 1000001},     // large values, expected -1 eventually
        {2, 2, 50, 100},              // general case
        {0, 0, 0, 0}                  // trivial
    };

    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            checksum += sol.minMoves(tc.sx, tc.sy, tc.tx, tc.ty);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << '\n';
    cout << "Elapsed time (ns): " << elapsed_ns << '\n';

    return 0;
}