#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <utility>

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
    vector<pair<string, int>> tests = {
        {"", 1},
        {"a", 1},
        {"aaaaa", 3},
        {"abcde", 2},
        {"aaabbcdddde", 7},
        {"ababababab", 5},
        {"zzzzzyyyyyxxxxx", 8},
        {"q", 10},
        {"mississippi", 6},
        {"aabbccddeeffgg", 9}
    };

    Solution sol;
    volatile unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            checksum += sol.possibleStringCount(t.first, t.second);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed milliseconds: " << elapsed_ms << "\n";

    return 0;
}