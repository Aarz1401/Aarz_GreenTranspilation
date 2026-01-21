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
