#include <iostream>
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

// Time:  O(m * n logk), where k is the possible maximum sum of loses
// Space: O(m + n)
class Solution2 {
public:
    // @param dungeon, a list of lists of integers
    // @return a integer
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int maximum_loses = 0;
        for (const auto& rooms : dungeon) {
            for (int room : rooms) {
                if (room < 0) {
                    maximum_loses += abs(room);
                }
            }
        }
        return binarySearch(dungeon, maximum_loses);
    }

private:
    int binarySearch(const vector<vector<int>>& dungeon, int maximum_loses) {
        int start = 1, end = maximum_loses + 1;
        while (start < end) {
            int mid = start + (end - start) / 2;
            if (DP(dungeon, mid)) {
                end = mid;
            } else {
                start = mid + 1;
            }
        }
        return start;
    }

    bool DP(const vector<vector<int>>& dungeon, int HP) {
        int m = dungeon.size();
        int n = dungeon[0].size();
        vector<int> remain_HP(n, 0);
        remain_HP[0] = HP + dungeon[0][0];

        for (int j = 1; j < n; ++j) {
            if (remain_HP[j - 1] > 0) {
                remain_HP[j] = max(remain_HP[j - 1] + dungeon[0][j], 0);
            }
        }

        for (int i = 1; i < m; ++i) {
            if (remain_HP[0] > 0) {
                remain_HP[0] = max(remain_HP[0] + dungeon[i][0], 0);
            } else {
                remain_HP[0] = 0;
            }

            for (int j = 1; j < n; ++j) {
                int remain = 0;
                if (remain_HP[j - 1] > 0) {
                    remain = max(remain_HP[j - 1] + dungeon[i][j], remain);
                }
                if (remain_HP[j] > 0) {
                    remain = max(remain_HP[j] + dungeon[i][j], remain);
                }
                remain_HP[j] = remain;
            }
        }

        return remain_HP[n - 1] > 0;
    }
};