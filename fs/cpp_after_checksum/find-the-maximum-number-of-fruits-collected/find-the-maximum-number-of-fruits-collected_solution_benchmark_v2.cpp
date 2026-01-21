#include <iostream>
#include <vector>
#include <algorithm>
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

volatile int sink = 0;

int main() {
    const vector<vector<vector<int>>> tests = {
        { {7} },
        { {1, 2}, {3, 4} },
        { {2, 0, 1}, {5, 3, 4}, {6, 7, 8} },
        { {0, 2, 3, 1}, {4, 0, 6, 2}, {7, 8, 0, 3}, {1, 5, 9, 0} },
        { {1, 2, 3, 4, 5}, {5, 4, 3, 2, 1}, {0, 1, 0, 1, 0}, {9, 8, 7, 6, 5}, {2, 2, 2, 2, 2} },
        { {1, 0, 2, 0, 3, 0}, {0, 4, 0, 5, 0, 6}, {7, 0, 8, 0, 9, 0}, {0, 1, 0, 2, 0, 3}, {4, 0, 5, 0, 6, 0}, {0, 7, 0, 8, 0, 9} },
        { {9, 1, 2, 3, 4, 5, 6}, {6, 5, 4, 3, 2, 1, 0}, {1, 3, 5, 7, 9, 2, 4}, {2, 4, 6, 8, 1, 3, 5}, {5, 3, 1, 0, 2, 4, 6}, {7, 5, 3, 1, 9, 8, 7}, {0, 2, 4, 6, 8, 1, 3} },
        { {0, 0, 1, 0, 1, 0, 1, 0}, {1, 2, 0, 2, 0, 2, 0, 2}, {3, 0, 3, 0, 3, 0, 3, 0}, {0, 4, 0, 4, 0, 4, 0, 4}, {5, 0, 5, 0, 5, 0, 5, 0}, {0, 6, 0, 6, 0, 6, 0, 6}, {7, 0, 7, 0, 7, 0, 7, 0}, {0, 8, 0, 8, 0, 8, 0, 8} },
        { {1, 1, 1, 1, 1, 1, 1, 1, 1}, {2, 3, 5, 7, 11, 13, 17, 19, 23}, {0, 1, 0, 1, 0, 1, 0, 1, 0}, {9, 8, 7, 6, 5, 4, 3, 2, 1}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, {9, 0, 8, 0, 7, 0, 6, 0, 5}, {5, 4, 3, 2, 1, 0, 1, 2, 3}, {3, 1, 4, 1, 5, 9, 2, 6, 5}, {8, 7, 6, 5, 4, 3, 2, 1, 0} },
        { {10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, {0, 2, 4, 6, 8, 10, 12, 14, 16, 18}, {18, 16, 14, 12, 10, 8, 6, 4, 2, 0}, {5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, {3, 1, 4, 1, 5, 9, 2, 6, 5, 3}, {2, 7, 1, 8, 2, 8, 1, 8, 2, 8}, {9, 3, 7, 9, 3, 7, 9, 3, 7, 9} }
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            auto input = t;
            checksum += sol.maxCollectedFruits(input);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}