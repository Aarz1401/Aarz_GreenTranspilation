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
    int maxCollectedFruits(vector<vector<int>>& fruits) {
        int n = fruits.size();
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n - (i + 1); ++j) {
                fruits[i][j] = 0;
            }
        }
        for (int i = 1; i < n - 1; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int a = fruits[i - 1][j - 1];
                int b = fruits[i - 1][j];
                int c = (j + 1 < n) ? fruits[i - 1][j + 1] : 0;
                fruits[i][j] += max(a, max(b, c));
            }
        }
        for (int j = 0; j < n; ++j) {
            for (int i = j + 1; i < n - (j + 1); ++i) {
                fruits[i][j] = 0;
            }
        }
        for (int j = 1; j < n - 1; ++j) {
            for (int i = j + 1; i < n; ++i) {
                int a = fruits[i - 1][j - 1];
                int b = fruits[i][j - 1];
                int c = (i + 1 < n) ? fruits[i + 1][j - 1] : 0;
                fruits[i][j] += max(a, max(b, c));
            }
        }
        long long result = 0;
        for (int i = 0; i < n; ++i) {
            result += fruits[i][i];
        }
        if (n >= 2) {
            result += fruits[n - 2][n - 1] + fruits[n - 1][n - 2];
        }
        return static_cast<int>(result);
    }
};

int main() {
    vector<vector<vector<int>>> origTests;
    origTests.reserve(10);

    // Test 1: n=1
    origTests.push_back({{5}});

    // Test 2: n=2
    origTests.push_back({
        {1, 2},
        {3, 4}
    });

    // Test 3: n=3
    origTests.push_back({
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    });

    // Test 4: n=4 all zeros
    {
        int n = 4;
        vector<vector<int>> t(n, vector<int>(n, 0));
        origTests.push_back(t);
    }

    // Test 5: n=5 diverse digits
    origTests.push_back({
        {3, 1, 4, 1, 5},
        {9, 2, 6, 5, 3},
        {5, 8, 9, 7, 9},
        {3, 2, 3, 8, 4},
        {6, 2, 6, 4, 3}
    });

    // Test 6: n=6 mixed negatives and positives
    origTests.push_back({
        {0,  -1,  2,  -3,  4,  -5},
        {6,  -7,  8,  -9, 10, -11},
        {12, -13, 14, -15, 16, -17},
        {18, -19, 20, -21, 22, -23},
        {24, -25, 26, -27, 28, -29},
        {30, -31, 32, -33, 34, -35}
    });

    // Test 7: n=7 programmatic moderate values
    {
        int n = 7;
        vector<vector<int>> t(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                t[i][j] = ((i + 1) * (j + 1) * 7) % 1000;
        origTests.push_back(t);
    }

    // Test 8: n=8 chessboard pattern
    {
        int n = 8;
        vector<vector<int>> t(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                t[i][j] = ((i + j) % 2 == 0) ? 100 : 1;
        origTests.push_back(t);
    }

    // Test 9: n=9 diagonal-heavy matrix
    {
        int n = 9;
        vector<vector<int>> t(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                t[i][j] = (i == j) ? 50 : abs(i - j);
        origTests.push_back(t);
    }

    // Test 10: n=10 LCG-filled matrix (deterministic)
    {
        auto lcg_next = [](unsigned int& state) {
            state = state * 1103515245u + 12345u;
            return state;
        };
        unsigned int state = 123456789u;
        int n = 10;
        vector<vector<int>> t(n, vector<int>(n));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                t[i][j] = static_cast<int>((lcg_next(state) >> 16) % 1000); // 0..999
        origTests.push_back(t);
    }

    Solution sol;
    long long checksum = 0;

    using chrono::high_resolution_clock;
    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t k = 0; k < origTests.size(); ++k) {
            vector<vector<int>> fruits = origTests[k]; // copy to avoid modifying originals
            int res = sol.maxCollectedFruits(fruits);
            checksum += res;
        }
    }

    auto end = high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed_ms = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms.count() << "\n";

    return 0;
}