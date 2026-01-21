#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <cstdint>

using namespace std;

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

int main() {
    // Define 10 diverse test inputs (strings as required by the solution)
    vector<string> tests = {
        "",    // empty
        "a",   // single lowercase
        "z",   // single lowercase end
        "A",   // single uppercase
        "ab",  // two lowercase ascending
        "ba",  // two lowercase descending
        "zz",  // two same end chars
        "aa",  // two same start chars
        "Az",  // mixed case
        "mm"   // two middle letters
    };

    Solution sol;
    uint64_t checksum = 0;

    using clock_type = std::chrono::high_resolution_clock;
    auto start = clock_type::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            string out = sol.minCostGoodCaption(tests[i]);
            // Mix output into checksum
            checksum += static_cast<uint64_t>(out.size());
            for (char c : out) {
                checksum = checksum * 1315423911u + static_cast<unsigned char>(c);
            }
            // Also mix input to avoid trivial zero checksum
            checksum += static_cast<uint64_t>(tests[i].size());
            if (!tests[i].empty()) {
                checksum ^= static_cast<uint64_t>(static_cast<unsigned char>(tests[i][0]));
            }
        }
    }

    auto end = clock_type::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";
    return 0;
}