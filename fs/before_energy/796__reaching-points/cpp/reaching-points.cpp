#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <utility>

using namespace std;

// Time:  O(log(max(m, n)))
// Space: O(1)

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        long long sxLL = sx, syLL = sy, txLL = tx, tyLL = ty;
        while (txLL >= sxLL && tyLL >= syLL) {
            if (txLL < tyLL) {
                std::swap(sxLL, syLL);
                std::swap(txLL, tyLL);
            }
            if (tyLL > syLL) {
                txLL %= tyLL;
            } else {
                return (txLL - sxLL) % tyLL == 0;
            }
        }
        return false;
    }
};