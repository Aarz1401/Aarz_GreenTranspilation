#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <array>
#include <algorithm>
#include <limits>
#include <utility>

class Solution {
public:
    int minSwap(std::vector<int>& A, std::vector<int>& B) {
        // Time:  O(n)
        // Space: O(1)
        int n = static_cast<int>(A.size());
        if (n <= 1) return 0;

        const int INF = std::numeric_limits<int>::max() / 4;
        std::array<int, 2> dp_no_swap = {0, 0};
        std::array<int, 2> dp_swap = {1, 1};

        for (int i = 1; i < n; ++i) {
            int cur = i & 1;
            int prev = (i - 1) & 1;
            dp_no_swap[cur] = INF;
            dp_swap[cur] = INF;

            if (A[i - 1] < A[i] && B[i - 1] < B[i]) {
                dp_no_swap[cur] = std::min(dp_no_swap[cur], dp_no_swap[prev]);
                dp_swap[cur] = std::min(dp_swap[cur], dp_swap[prev] + 1);
            }
            if (A[i - 1] < B[i] && B[i - 1] < A[i]) {
                dp_no_swap[cur] = std::min(dp_no_swap[cur], dp_swap[prev]);
                dp_swap[cur] = std::min(dp_swap[cur], dp_no_swap[prev] + 1);
            }
        }
        return std::min(dp_no_swap[(n - 1) & 1], dp_swap[(n - 1) & 1]);
    }
};

int main() {
    std::vector<std::pair<std::vector<int>, std::vector<int>>> tests;
    tests.reserve(10);

    // 1
    tests.push_back({{1}, {2}});
    // 2
    tests.push_back({{1, 3, 5, 4}, {1, 2, 3, 7}});
    // 3
    tests.push_back({{1, 200, 3, 400, 5, 600, 7, 800}, {100, 2, 300, 4, 500, 6, 700, 8}});
    // 4
    tests.push_back({{1, 3, 5, 7, 9}, {2, 4, 6, 8, 10}});
    // 5
    tests.push_back({{2, 4, 6, 8, 10}, {1, 3, 5, 7, 9}});
    // 6
    tests.push_back({{-5, -2, 1, 3, 4, 9}, {-4, -3, 0, 2, 7, 10}});
    // 7
    tests.push_back({{100, 2, 300, 4, 500, 6}, {1, 200, 3, 400, 5, 600}});
    // 8
    tests.push_back({{1, 3, 7, 9, 13}, {2, 4, 8, 10, 14}});
    // 9
    tests.push_back({{1, 3, 3, 5}, {1, 2, 4, 4}});
    // 10
    tests.push_back({{10, 2, 30, 4, 50, 6, 70, 8, 90, 10, 110, 12}, {1, 20, 3, 40, 5, 60, 7, 80, 9, 100, 11, 120}});

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            int r = sol.minSwap(t.first, t.second);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}