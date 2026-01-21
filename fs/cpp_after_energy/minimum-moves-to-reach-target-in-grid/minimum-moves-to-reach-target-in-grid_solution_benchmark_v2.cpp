#include <vector>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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
    vector<TestCase> tests = {
        {0, 1, 0, 1},
        {0, 1, 2, 3},
        {0, 3, 6, 9},
        {5, 0, 20, 25},
        {0, 7, 56, 63},
        {1, 1, 3, 5},
        {2, 2, 4, 6},
        {0, 1, 536870912, 805306368},
        {7, 0, 112, 119},
        {1, 2, 1, 1}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            int r = sol.minMoves(tc.sx, tc.sy, tc.tx, tc.ty);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}