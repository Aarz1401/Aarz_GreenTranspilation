#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <queue>
#include <tuple>
#include <functional>
#include <algorithm>

using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size();
        if (m == 0) return 0;
        int n = heightMap[0].size();
        if (n == 0) return 0;

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        using T = tuple<int, int, int>;
        priority_queue<T, vector<T>, greater<T>> heap;

        for (int i = 0; i < m; ++i) {
            heap.emplace(heightMap[i][0], i, 0);
            visited[i][0] = true;
            heap.emplace(heightMap[i][n - 1], i, n - 1);
            visited[i][n - 1] = true;
        }
        for (int j = 1; j <= n - 2; ++j) {
            heap.emplace(heightMap[0][j], 0, j);
            visited[0][j] = true;
            heap.emplace(heightMap[m - 1][j], m - 1, j);
            visited[m - 1][j] = true;
        }

        long long trap = 0;
        static const int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        while (!heap.empty()) {
            auto [height, i, j] = heap.top();
            heap.pop();
            for (int k = 0; k < 4; ++k) {
                int x = i + dirs[k][0];
                int y = j + dirs[k][1];
                if (0 <= x && x < m && 0 <= y && y < n && !visited[x][y]) {
                    trap += max(0, height - heightMap[x][y]);
                    heap.emplace(max(height, heightMap[x][y]), x, y);
                    visited[x][y] = true;
                }
            }
        }

        return static_cast<int>(trap);
    }
};

volatile int sink = 0;

int main() {
    vector<vector<vector<int>>> tests = {
        { {1,4,3}, {3,1,5}, {2,2,2} },
        { {3,3,3}, {3,3,3}, {3,3,3} },
        { {1,0,2,1,0} },
        { {5,5,5,5,5},
          {5,1,2,1,5},
          {5,2,1,2,5},
          {5,1,2,1,5},
          {5,5,5,5,5} },
        { {1,2,3,4},
          {2,3,4,5},
          {3,4,5,6},
          {4,5,6,7} },
        { {3,3,3},
          {3,1,3} },
        { {5,5,5,5},
          {5,1,4,5},
          {5,5,5,5} },
        { {8,8,8,8,8,8},
          {8,2,3,4,3,8},
          {8,3,1,2,4,8},
          {8,4,2,1,3,8},
          {8,3,4,3,2,8},
          {8,8,8,8,8,8} },
        { {2,2,2},
          {2,0,2},
          {2,2,2} },
        { {9,9,9,9,9},
          {9,1,8,1,9},
          {9,9,9,9,9} }
    };

    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            int r = sol.trapRainWater(tests[i]);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }
    return 0;
}