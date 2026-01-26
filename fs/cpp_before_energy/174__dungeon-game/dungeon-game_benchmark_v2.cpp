#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

// Time:  O(m * n)
// Space: O(m + n)
class Solution {
public:
    // @param dungeon, a list of lists of integers
    // @return a integer
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<int> DP(n, numeric_limits<int>::max());
        DP[n - 1] = 1;

        for (int i = m - 1; i >= 0; --i) {
            DP[n - 1] = max(DP[n - 1] - dungeon[i][n - 1], 1);
            for (int j = n - 2; j >= 0; --j) {
                int min_HP_on_exit = min(DP[j], DP[j + 1]);
                DP[j] = max(min_HP_on_exit - dungeon[i][j], 1);
            }
        }

        return DP[0];
    }
};

int main() {
    vector<vector<vector<int>>> tests = {
        {{-1}},
        {{5}},
        {{-2, -3, 3, -1}},
        {{-2}, {-3}, {3}, {-5}},
        {{-2, -2}, {-2, -2}},
        {{1, 2, 3}, {4, 5, 6}},
        {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}},
        {{0, -1, 0, -2}, {1, 0, -3, 0}, {-2, 4, 0, -1}, {0, -2, 3, 0}},
        {{1}, {1}, {1}, {1}, {1}},
        {{-1000, 1000, -1000, 1}, {1, -1, -1, 1000}, {999, -999, 500, -500}}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        Solution sol;
        for (size_t i = 0; i < tests.size(); ++i) {
            int r = sol.calculateMinimumHP(tests[i]);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }
    return 0;
}