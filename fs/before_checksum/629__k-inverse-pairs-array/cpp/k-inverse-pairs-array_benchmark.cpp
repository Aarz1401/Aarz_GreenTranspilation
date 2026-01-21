#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
using namespace std;

// Time:  O(n * k)
// Space: O(k)
// knapsack dp, combinatorics, sliding window, two pointers
class Solution {
public:
    int kInversePairs(int n, int k) {
        static const int MOD = 1000000007;
        if (k > n * (n - 1) / 2) return 0;
        if (k == 0) return 1;

        vector<int> dp(k + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n; ++i) {
            vector<int> new_dp(k + 1, 0);
            long long curr = 0;
            for (int j = 0; j <= k; ++j) {
                curr += dp[j];
                if (curr >= MOD) curr -= MOD;
                if (j - (i + 1) >= 0) {
                    curr -= dp[j - (i + 1)];
                    if (curr < 0) curr += MOD;
                }
                new_dp[j] = static_cast<int>(curr);
            }
            dp.swap(new_dp);
        }
        return dp[k];
    }
};

int main() {
    // Define 10 diverse test inputs (n, k)
    vector<pair<int, int>> tests = {
        {1, 0},    // minimal case
        {2, 1},    // small, single inversion
        {3, 0},    // zero inversions
        {3, 4},    // k > max inversions -> should return 0
        {4, 5},    // near max for n=4 (max=6)
        {5, 10},   // exactly max for n=5
        {10, 12},  // moderate
        {20, 50},  // larger moderate
        {100, 0},  // large n, zero inversions
        {200, 100} // larger n, moderate k
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int n = tests[i].first;
            int k = tests[i].second;
            int result = sol.kInversePairs(n, k);
            checksum += result;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}