#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <utility>
#include <vector>
#include <array>

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

int main() {
    Solution sol;
    std::vector<std::array<int, 4>> tests = {
        std::array<int,4>{1, 1, 3, 5},           // true
        std::array<int,4>{1, 1, 2, 2},           // false
        std::array<int,4>{1, 3, 10, 3},          // true
        std::array<int,4>{3, 1, 3, 10},          // true
        std::array<int,4>{1, 1, 1000000000, 1},  // true
        std::array<int,4>{2, 3, 1000000000, 1000000000}, // false
        std::array<int,4>{5, 7, 33, 7},          // true
        std::array<int,4>{9, 5, 58, 37},         // false
        std::array<int,4>{3, 7, 2, 100},         // false
        std::array<int,4>{2, 4, 30, 4}           // true
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            int r = sol.reachingPoints(t[0], t[1], t[2], t[3]);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}