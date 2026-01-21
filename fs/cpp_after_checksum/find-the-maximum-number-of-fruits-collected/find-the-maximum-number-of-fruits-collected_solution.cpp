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
