#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>
#include <limits>
#include <chrono>
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
    // Define 10 diverse test cases
    vector<vector<vector<int>>> tests;
    tests.reserve(10);

    // 1. Single positive cell
    tests.push_back({{5}});

    // 2. Single negative cell
    tests.push_back({{-5}});

    // 3. 1x5 row with mixed values
    tests.push_back({{-2, -3, 3, -1, 4}});

    // 4. 5x1 column with mixed values
    tests.push_back({{-2}, {-3}, {3}, {-1}, {4}});

    // 5. 2x2 mixed grid
    tests.push_back({{-2, -3}, {10, -5}});

    // 6. Standard example grid
    tests.push_back({{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}});

    // 7. All positive values
    tests.push_back({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}});

    // 8. All zeros
    tests.push_back({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

    // 9. Large negative values
    tests.push_back({{-100, -200, -300}, {-400, -500, -600}, {-700, -800, -900}});

    // 10. 10x10 alternating -1 and 1
    {
        vector<vector<int>> grid(10, vector<int>(10));
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                grid[i][j] = ((i + j) % 2 == 0) ? -1 : 1;
            }
        }
        tests.push_back(grid);
    }

    Solution solver;
    volatile long long checksum = 0; // volatile to prevent optimization of accumulation

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            // Make a local copy to strictly adhere to non-const reference without risking aliasing assumptions
            vector<vector<int>> dungeon = tests[i];
            int res = solver.calculateMinimumHP(dungeon);
            checksum += (res ^ static_cast<int>(i) ^ iter);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}