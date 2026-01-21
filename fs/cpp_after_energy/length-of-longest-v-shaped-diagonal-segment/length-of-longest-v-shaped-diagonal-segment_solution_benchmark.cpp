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
#include <random>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int lenOfVDiagonal(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int result = 0;
        vector<vector<int>> down_right(n, vector<int>(m, 1));
        vector<vector<int>> down_left(n, vector<int>(m, 1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x = grid[i][j];
                if (x == 1) {
                    result = max(result, 1);
                    continue;
                }
                if (i - 1 >= 0 && j - 1 >= 0 && grid[i - 1][j - 1] == 2 - x) {
                    down_right[i][j] = down_right[i - 1][j - 1] + 1;
                }
                if (i - 1 >= 0 && j + 1 < m && grid[i - 1][j + 1] == 2 - x) {
                    down_left[i][j] = down_left[i - 1][j + 1] + 1;
                }
            }
        }
        vector<vector<int>> up_right(n, vector<int>(m, 1));
        vector<vector<int>> up_left(n, vector<int>(m, 1));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < m; ++j) {
                int x = grid[i][j];
                if (x == 1) {
                    continue;
                }
                if (i + 1 < n && j - 1 >= 0 && grid[i + 1][j - 1] == 2 - x) {
                    up_right[i][j] = up_right[i + 1][j - 1] + 1;
                }
                if (i + 1 < n && j + 1 < m && grid[i + 1][j + 1] == 2 - x) {
                    up_left[i][j] = up_left[i + 1][j + 1] + 1;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int x = grid[i][j];
                if (x == 1) {
                    continue;
                }
                if (((down_right[i][j] % 2 == 0) && x == 0) || ((down_right[i][j] % 2 == 1) && x == 2)) {
                    int ni = i - down_right[i][j];
                    int nj = j - down_right[i][j];
                    if (0 <= ni && ni < n && 0 <= nj && nj < m && grid[ni][nj] == 1) {
                        result = max(result, down_right[i][j] + up_right[i][j]);  // >
                    }
                }
                if (((down_left[i][j] % 2 == 0) && x == 0) || ((down_left[i][j] % 2 == 1) && x == 2)) {
                    int ni = i - down_left[i][j];
                    int nj = j + down_left[i][j];
                    if (0 <= ni && ni < n && 0 <= nj && nj < m && grid[ni][nj] == 1) {
                        result = max(result, down_left[i][j] + down_right[i][j]);  // v
                    }
                }
                if (((up_left[i][j] % 2 == 0) && x == 0) || ((up_left[i][j] % 2 == 1) && x == 2)) {
                    int ni = i + up_left[i][j];
                    int nj = j + up_left[i][j];
                    if (0 <= ni && ni < n && 0 <= nj && nj < m && grid[ni][nj] == 1) {
                        result = max(result, up_left[i][j] + down_left[i][j]);  // <
                    }
                }
                if (((up_right[i][j] % 2 == 0) && x == 0) || ((up_right[i][j] % 2 == 1) && x == 2)) {
                    int ni = i + up_right[i][j];
                    int nj = j - up_right[i][j];
                    if (0 <= ni && ni < n && 0 <= nj && nj < m && grid[ni][nj] == 1) {
                        result = max(result, up_right[i][j] + up_left[i][j]);  // ^
                    }
                }
            }
        }
        return result;
    }
};

static vector<vector<int>> makeCheckerboard(int n, int m, int oneStride = 0) {
    vector<vector<int>> g(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            g[i][j] = ((i + j) % 2 == 0) ? 0 : 2;
            if (oneStride > 0 && ((i + j) % oneStride == 0)) g[i][j] = 1;
        }
    }
    return g;
}

static vector<vector<int>> makeRandomGrid(int n, int m, uint32_t seed, double p1 = 0.15) {
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> ud(0.0, 1.0);
    vector<vector<int>> g(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            double r = ud(rng);
            if (r < p1) g[i][j] = 1;
            else g[i][j] = (ud(rng) < 0.5 ? 0 : 2);
        }
    }
    return g;
}

int main() {
    // Define 10 diverse test inputs
    vector<vector<vector<int>>> tests;
    // 1) 1x1 all ones
    tests.push_back({{1}});
    // 2) Small manual mixed grid
    tests.push_back({{1, 0, 2}, {2, 1, 0}});
    // 3) 3x5 checkerboard with some 1s
    {
        auto g = makeCheckerboard(3, 5, 3);
        g[0][2] = 1; g[2][2] = 1;
        tests.push_back(g);
    }
    // 4) 5x5 random
    tests.push_back(makeRandomGrid(5, 5, 42u, 0.2));
    // 5) 10x10 random
    tests.push_back(makeRandomGrid(10, 10, 123u, 0.1));
    // 6) 7x9 checkerboard with diagonal ones
    {
        auto g = makeCheckerboard(7, 9);
        for (int i = 0; i < 7 && i < 9; ++i) g[i][i] = 1;
        tests.push_back(g);
    }
    // 7) 20x20 stripes with periodic ones
    {
        vector<vector<int>> g(20, vector<int>(20, 0));
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 20; ++j) {
                if ((i + j) % 7 == 0) g[i][j] = 1;
                else g[i][j] = ((i + j) % 2 == 0) ? 0 : 2;
            }
        }
        tests.push_back(g);
    }
    // 8) 15x15 with center cross of ones
    {
        vector<vector<int>> g(15, vector<int>(15, 0));
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                g[i][j] = ((i + j) % 2 == 0) ? 0 : 2;
            }
        }
        int c = 7;
        for (int i = 0; i < 15; ++i) { g[i][c] = 1; g[c][i] = 1; }
        tests.push_back(g);
    }
    // 9) 1x10 row alternating with ones at both ends
    {
        vector<vector<int>> g(1, vector<int>(10, 0));
        for (int j = 0; j < 10; ++j) g[0][j] = (j % 2 == 0) ? 0 : 2;
        g[0][0] = 1; g[0][9] = 1;
        tests.push_back(g);
    }
    // 10) 30x30 random dense
    tests.push_back(makeRandomGrid(30, 30, 987u, 0.12));

    Solution sol;
    long long checksum = 0;

    auto t0 = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            // Use by reference to avoid copy; function takes non-const reference
            checksum += sol.lenOfVDiagonal(tests[t]);
            checksum ^= (static_cast<long long>(t) << (iter % 7)); // perturb checksum
        }
    }
    auto t1 = std::chrono::high_resolution_clock::now();

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed << "\n";

    return 0;
}