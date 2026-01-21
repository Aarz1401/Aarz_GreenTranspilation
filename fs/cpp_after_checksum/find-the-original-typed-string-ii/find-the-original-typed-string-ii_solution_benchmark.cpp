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
#include <cstdint>

using namespace std;

class Solution {
public:
    int possibleStringCount(string word, int k) {
        const int MOD = 1000000007;
        vector<int> cnt;
        int current = 0;
        for (int i = 0; i < static_cast<int>(word.size()); ++i) {
            current += 1;
            if (i + 1 == static_cast<int>(word.size()) || word[i + 1] != word[i]) {
                cnt.push_back(current);
                current = 0;
            }
        }
        long long result = 1;
        for (int l : cnt) {
            result = (result * l) % MOD;
        }
        if (k <= static_cast<int>(cnt.size())) {
            return static_cast<int>(result);
        }
        int m = k - static_cast<int>(cnt.size());
        vector<long long> dp(m, 0);
        dp[0] = 1;
        for (int l : cnt) {
            for (int i = 0; i < m - 1; ++i) {
                dp[i + 1] = (dp[i + 1] + dp[i]) % MOD;
            }
            for (int i = m - 1; i >= l; --i) {
                dp[i] = (dp[i] - dp[i - l]) % MOD;
                if (dp[i] < 0) dp[i] += MOD;
            }
        }
        long long sumdp = 0;
        for (int i = 0; i < m; ++i) {
            sumdp = (sumdp + dp[i]) % MOD;
        }
        long long ans = (result - sumdp) % MOD;
        if (ans < 0) ans += MOD;
        return static_cast<int>(ans);
    }
};

int main() {
    // Prepare 10 diverse test inputs
    vector<pair<string, int>> tests;
    tests.emplace_back("", 0);                              // Empty string, k = 0
    tests.emplace_back("a", 1);                             // Single character, k = runs
    tests.emplace_back("aaaaaa", 3);                        // Single run, k > runs
    tests.emplace_back("ababababab", 5);                    // Alternating chars, k < runs
    tests.emplace_back("aaabbbcccddd", 4);                  // Multiple equal runs, k = runs
    tests.emplace_back("zzzzzyxxxx", 7);                    // Mixed runs, k > runs
    tests.emplace_back("a1a1a1bbbccddeeee", 12);            // Alphanumeric with varied runs, moderate k
    tests.emplace_back("abcdef", 3);                        // All unique, k < runs
    {
        string base = "abcdefghijklmnopqrstuvwxyz";
        string longPattern;
        for (int i = 0; i < 20; ++i) longPattern += base;   // 520 chars, all runs of length 1
        tests.emplace_back(longPattern, 100);               // k < runs to avoid DP branch
    }
    tests.emplace_back(string(300, 'b') + string(200, 'c'), 50); // Two long runs, k > runs but m < run lengths

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            checksum += static_cast<uint64_t>(sol.possibleStringCount(tc.first, tc.second));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed << "\n";

    return 0;
}