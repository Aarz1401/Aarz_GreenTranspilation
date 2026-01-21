#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <cstdint>
#include <chrono>

using namespace std;

class Solution {
public:
    int numDecodings(string s) {
        const long long M = 1000000007LL;
        const int W = 3;
        int n = static_cast<int>(s.size());
        vector<long long> dp(W, 0);
        dp[0] = 1;
        if (s[0] == '*') {
            dp[1] = 9;
        } else if (s[0] != '0') {
            dp[1] = dp[0];
        } else {
            dp[1] = 0;
        }
        for (int i = 1; i < n; ++i) {
            int cur = (i + 1) % W;
            int prev = i % W;
            int prevprev = (i - 1) % W;
            if (s[i] == '*') {
                dp[cur] = (9LL * dp[prev]) % M;
                if (s[i - 1] == '1') {
                    dp[cur] = (dp[cur] + 9LL * dp[prevprev]) % M;
                } else if (s[i - 1] == '2') {
                    dp[cur] = (dp[cur] + 6LL * dp[prevprev]) % M;
                } else if (s[i - 1] == '*') {
                    dp[cur] = (dp[cur] + 15LL * dp[prevprev]) % M;
                }
            } else {
                dp[cur] = (s[i] != '0') ? dp[prev] % M : 0;
                if (s[i - 1] == '1') {
                    dp[cur] = (dp[cur] + dp[prevprev]) % M;
                } else if (s[i - 1] == '2' && s[i] <= '6') {
                    dp[cur] = (dp[cur] + dp[prevprev]) % M;
                } else if (s[i - 1] == '*') {
                    long long add = (s[i] <= '6') ? 2LL : 1LL;
                    dp[cur] = (dp[cur] + add * dp[prevprev]) % M;
                }
            }
        }
        return static_cast<int>(dp[n % W] % M);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> tests;
    tests.emplace_back("12");           // simple digits
    tests.emplace_back("*");            // single wildcard
    tests.emplace_back("1*");           // '1' followed by wildcard
    tests.emplace_back("2*");           // '2' followed by wildcard
    tests.emplace_back("**");           // double wildcard
    tests.emplace_back("0");            // invalid single zero
    tests.emplace_back("10*");          // zero handling with valid prefix
    tests.emplace_back("26*");          // boundary with '2' and wildcard
    tests.emplace_back("230");          // invalid zero after '3'
    tests.emplace_back(string(100, '*'));// long all-wildcards

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += sol.numDecodings(s);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}