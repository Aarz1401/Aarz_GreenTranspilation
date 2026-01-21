#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Time:  O(n * p * g)
// Space: O(p * g)

class Solution {
public:
    int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
        const int MOD = 1000000007;
        int G = n, P = minProfit;
        vector<vector<int>> dp(P + 1, vector<int>(G + 1, 0));
        dp[0][0] = 1;
        for (size_t idx = 0; idx < group.size(); ++idx) {
            int g = group[idx];
            int p = profit[idx];
            for (int i = P; i >= 0; --i) {
                int ni = min(P, i + p);
                for (int j = G - g; j >= 0; --j) {
                    if (dp[i][j]) {
                        int nj = j + g;
                        dp[ni][nj] += dp[i][j];
                        if (dp[ni][nj] >= MOD) dp[ni][nj] -= MOD;
                    }
                }
            }
        }
        int ans = 0;
        for (int j = 0; j <= G; ++j) {
            ans += dp[P][j];
            if (ans >= MOD) ans -= MOD;
        }
        return ans;
    }
};

struct Test {
    int n;
    int minProfit;
    vector<int> group;
    vector<int> profit;
};

int main() {
    vector<Test> tests = {
        {1, 0, {1}, {1}},
        {5, 3, {2, 2}, {2, 3}},
        {10, 10, {2, 3, 5, 4}, {6, 7, 8, 2}},
        {5, 1, {1, 2, 3}, {0, 1, 2}},
        {8, 6, {2, 2, 2, 2}, {1, 2, 3, 4}},
        {10, 15, {2, 2, 2, 2, 2}, {1, 2, 1, 3, 3}},
        {100, 100, vector<int>(20, 5), vector<int>(20, 5)},
        {64, 32, {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}, {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4}},
        {3, 3, {1, 1, 1}, {1, 1, 1}},
        {50, 0, vector<int>(10, 5), {0,1,2,3,4,5,6,7,8,9}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<int> g = t.group;
            vector<int> p = t.profit;
            checksum += sol.profitableSchemes(t.n, t.minProfit, g, p);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}