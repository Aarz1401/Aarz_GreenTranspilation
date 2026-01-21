#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <algorithm>

using namespace std;

// Time:  O(n^2)
// Space: O(n)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }
        int result = 0;
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> heights(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                heights[j] = (matrix[i][j] == '1') ? heights[j] + 1 : 0;
            }
            result = max(result, largestRectangleArea(heights));
        }
        return result;
    }

private:
    int largestRectangleArea(const vector<int>& heights) {
        vector<int> stk;
        stk.push_back(-1);
        int result = 0;
        int n = heights.size();
        for (int i = 0; i <= n; ++i) {
            while (stk.back() != -1 && (i == n || heights[stk.back()] >= heights[i])) {
                int h = heights[stk.back()];
                stk.pop_back();
                int width = (i - 1) - stk.back();
                result = max(result, h * width);
            }
            stk.push_back(i);
        }
        return result;
    }
};

static vector<vector<char>> makeMatrix(const vector<string>& lines) {
    vector<vector<char>> m;
    m.reserve(lines.size());
    for (const auto& s : lines) {
        m.emplace_back(s.begin(), s.end());
    }
    return m;
}

int main() {
    // Prepare 10 diverse test inputs
    vector<vector<vector<char>>> testCases;
    testCases.reserve(10);

    // 1) Empty matrix
    testCases.push_back(vector<vector<char>>{});

    // 2) Matrix with zero columns
    testCases.push_back(makeMatrix({"", "", ""}));

    // 3) Single cell '0'
    testCases.push_back(makeMatrix({"0"}));

    // 4) Single cell '1'
    testCases.push_back(makeMatrix({"1"}));

    // 5) Single row mixed
    testCases.push_back(makeMatrix({"1011010011001110"}));

    // 6) Single column mixed
    testCases.push_back(makeMatrix({"1","0","1","1","1","1","0","1"}));

    // 7) All zeros 5x5
    testCases.push_back(makeMatrix({"00000","00000","00000","00000","00000"}));

    // 8) All ones 5x7
    testCases.push_back(makeMatrix({"1111111","1111111","1111111","1111111","1111111"}));

    // 9) Checkerboard 6x6 starting with '1'
    {
        vector<string> lines(6, string(6, '0'));
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 6; ++j) {
                lines[i][j] = ((i + j) % 2 == 0) ? '1' : '0';
            }
        }
        testCases.push_back(makeMatrix(lines));
    }

    // 10) Mixed example
    testCases.push_back(makeMatrix({"10100","10111","11111","10010"}));

    Solution sol;
    long long checksum = 0;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < testCases.size(); ++i) {
            checksum += sol.maximalRectangle(testCases[i]);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}