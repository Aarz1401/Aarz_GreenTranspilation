#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <array>
#include <string>
#include <functional>
#include <cstdint>
#include <chrono>

using namespace std;

class Solution {
public:
    int countPalindromicSubsequences(string S) {
        const int MOD = 1000000007;
        int n = S.size();
        if (n == 0) return 0;

        vector<array<int, 4>> prv(n), nxt(n);

        array<int, 4> last;
        last.fill(-1);
        for (int i = 0; i < n; ++i) {
            last[S[i] - 'a'] = i;
            prv[i] = last;
        }

        last.fill(-1);
        for (int i = n - 1; i >= 0; --i) {
            last[S[i] - 'a'] = i;
            nxt[i] = last;
        }

        vector<vector<long long>> memo(n, vector<long long>(n, -1));

        function<long long(int, int)> dp = [&](int i, int j) -> long long {
            if (memo[i][j] != -1) return memo[i][j];
            long long result = 1;
            if (i <= j) {
                for (int x = 0; x < 4; ++x) {
                    int i0 = nxt[i][x];
                    int j0 = prv[j][x];
                    if (i0 != -1 && i0 >= i && i0 <= j) {
                        result = (result + 1) % MOD;
                    }
                    if (i0 != -1 && j0 != -1 && i0 < j0) {
                        result = (result + dp(i0 + 1, j0 - 1)) % MOD;
                    }
                }
            }
            result %= MOD;
            memo[i][j] = result;
            return result;
        };

        long long ans = dp(0, n - 1);
        ans = (ans - 1 + MOD) % MOD;  // subtract empty subsequence
        return static_cast<int>(ans);
    }
};

int main() {
    vector<string> tests = {
        "",
        "a",
        "aa",
        "ab",
        "abcd",
        "dcba",
        "aaaabbbbccccdddd",
        "ababababcdcdcdcd",
        "abccbaabccba",
        "dacabadacabadacaba"
    };

    Solution sol;
    uint64_t checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += static_cast<uint64_t>(sol.countPalindromicSubsequences(s));
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}