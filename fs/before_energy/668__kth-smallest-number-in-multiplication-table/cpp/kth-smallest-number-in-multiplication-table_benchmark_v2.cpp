#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <algorithm>
#include <vector>
#include <array>

class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        auto count = [&](long long target) -> long long {
            long long cnt = 0;
            for (int i = 1; i <= m; ++i) {
                cnt += std::min<long long>(target / i, n);
            }
            return cnt;
        };

        long long left = 1, right = 1LL * m * n;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (count(mid) >= k) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return static_cast<int>(left);
    }
};

int main() {
    std::vector<std::array<int, 3>> tests = {
        std::array<int,3>{1, 1, 1},
        std::array<int,3>{1, 10, 7},
        std::array<int,3>{10, 1, 4},
        std::array<int,3>{3, 3, 5},
        std::array<int,3>{2, 3, 6},
        std::array<int,3>{15, 20, 150},
        std::array<int,3>{20, 15, 213},
        std::array<int,3>{43, 47, 1000},
        std::array<int,3>{100, 100, 1000},
        std::array<int,3>{200, 150, 12345}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            int r = sol.findKthNumber(t[0], t[1], t[2]);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}