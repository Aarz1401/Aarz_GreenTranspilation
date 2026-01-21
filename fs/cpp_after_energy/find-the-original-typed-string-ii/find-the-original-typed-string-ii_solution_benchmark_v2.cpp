#include <vector>
#include <string>
#include <utility>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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
        {"a", 1},
        {"aaab", 3},
        {"abc", 3},
        {"aabbcc", 5},
        {"ababab", 4},
        {"zzzzzzzzzz", 7},
        {"mississippi", 10},
        {"qwertyuiopasdfghjkl", 20},
        {"aaaabbbbccccddddeeee", 2},
        {"b", 100}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            int r = sol.possibleStringCount(tc.first, tc.second);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}