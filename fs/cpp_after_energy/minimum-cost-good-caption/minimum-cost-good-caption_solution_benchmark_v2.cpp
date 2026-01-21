#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    string minCostGoodCaption(string caption) {
        const int L = 3;
        int n = static_cast<int>(caption.size());
        if (n < L) {
            return "";
        }
        vector<int> cap(n);
        for (int i = 0; i < n; ++i) {
            cap[i] = caption[i] - 'a';
        }
        int m = n - L + 1;
        vector<vector<array<int, 2>>> dp(m, vector<array<int, 2>>(26, {0, 0})); // {cost, len}
        vector<array<int, 2>> mn(m, {0, 0}); // {min_cost, argmin_j}

        for (int i = m - 1; i >= 0; --i) {
            for (int j = 0; j < 26; ++j) {
                if (i == m - 1) {
                    int cost = 0;
                    for (int k = i; k < i + L; ++k) {
                        cost += std::abs(cap[k] - j);
                    }
                    dp[i][j][0] = cost;
                    dp[i][j][1] = L;
                    continue;
                }
                // Option 1: length 1 block
                int cost1 = dp[i + 1][j][0] + std::abs(cap[i] - j);
                dp[i][j][0] = cost1;
                dp[i][j][1] = 1;

                // Option 2: length L block
                if (i + L < n - 2) {
                    int curr = mn[i + L][0];
                    for (int k = i; k < i + L; ++k) {
                        curr += std::abs(cap[k] - j);
                    }
                    int c = mn[i + L][1];
                    if (curr < dp[i][j][0] || (curr == dp[i][j][0] && c < j)) {
                        dp[i][j][0] = curr;
                        dp[i][j][1] = L;
                    }
                }
            }
            // compute mn[i] = min over j of (dp[i][j].cost, j)
            int bestCost = INT_MAX;
            int bestJ = 0;
            for (int j = 0; j < 26; ++j) {
                int cost = dp[i][j][0];
                if (cost < bestCost || (cost == bestCost && j < bestJ)) {
                    bestCost = cost;
                    bestJ = j;
                }
            }
            mn[i][0] = bestCost;
            mn[i][1] = bestJ;
        }

        string result;
        result.reserve(n);
        int i = 0;
        int j = mn[0][1];
        int l = 1;
        while (i != n) {
            if (l == L) {
                j = mn[i][1];
            }
            l = dp[i][j][1];
            result.append(l, static_cast<char>('a' + j));
            i += l;
        }
        return result;
    }
};

volatile int sink = 0;

int main() {
    vector<string> tests = {
        "abc",
        "zzz",
        "azbycxd",
        "helloworld",
        "abcdefghijklmnopqrstuvwxyz",
        "qwertyuiopasdfghjklzxcvbnm",
        "aaaaabbbbbcccccdddddeeeee",
        "mmmmmm",
        "nyanpasu",
        "babababababababababa"
    };

    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& s : tests) {
            string r = sol.minCostGoodCaption(s);
            DoNotOptimize(r); 
            //checksum += static_cast<int>(r[0]);
        }
        //sink = checksum;
    }

    return 0;
}