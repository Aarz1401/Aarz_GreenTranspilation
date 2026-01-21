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

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int longestPalindrome(string s, string t) {
        auto manacher = [&](const string& str) -> vector<int> {
            string T;
            T.reserve(2 * str.size() + 3);
            T.push_back('^');
            T.push_back('#');
            for (char c : str) {
                T.push_back(c);
                T.push_back('#');
            }
            T.push_back('$');

            int n = T.size();
            vector<int> P(n, 0);
            int C = 0, R = 0;
            for (int i = 1; i < n - 1; ++i) {
                int i_mirror = 2 * C - i;
                if (R > i) {
                    P[i] = min(R - i, P[i_mirror]);
                }
                while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                    ++P[i];
                }
                if (i + P[i] > R) {
                    C = i;
                    R = i + P[i];
                }
            }
            return P;
        };

        auto longest_palindrome = [&](const string& str) -> vector<int> {
            vector<int> res(str.size() + 1, 0);
            vector<int> P = manacher(str);
            for (int i = 1; i < static_cast<int>(P.size()) - 1; ++i) {
                int start = (i - P[i]) / 2;
                res[start] = P[i];
            }
            return res;
        };

        string rt = t;
        reverse(rt.begin(), rt.end());
        vector<int> p1 = longest_palindrome(s);
        vector<int> p2 = longest_palindrome(rt);

        int n = s.size();
        int m = rt.size();
        int ans = 0;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                bool match = (s[i] == rt[j]);
                dp[i + 1][j + 1] = match ? dp[i][j] + 2 : 0;
                int idxS = i + (match ? 1 : 0);
                int idxT = j + (match ? 1 : 0);
                ans = max(ans, dp[i + 1][j + 1] + max(p1[idxS], p2[idxT]));
            }
        }
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Generate 10 diverse test inputs (pairs of strings)
    vector<pair<string, string>> tests;
    tests.reserve(10);

    // 1. Both empty
    tests.emplace_back("", "");

    // 2. One empty, one single character
    tests.emplace_back("a", "");

    // 3. No common characters
    tests.emplace_back("abc", "def");

    // 4. Both palindromic
    tests.emplace_back("abba", "abba");

    // 5. Same single repeated character, different lengths
    tests.emplace_back(string(120, 'a'), string(110, 'a'));

    // 6. Alphabet repeated vs reverse alphabet repeated
    {
        string s, t;
        string a = "abcdefghijklmnopqrstuvwxyz";
        string ar = a;
        reverse(ar.begin(), ar.end());
        for (int i = 0; i < 3; ++i) { s += a; t += ar; }
        tests.emplace_back(s, t);
    }

    // 7. Embedded palindrome vs another palindrome
    tests.emplace_back("xyzracecarxyz", "abcdefgfedcba");

    // 8. Deterministic pseudo-random-like sequences
    {
        string s, t;
        s.reserve(100);
        t.reserve(120);
        for (int i = 0; i < 100; ++i) s.push_back(char('a' + (i * 7) % 26));
        for (int i = 0; i < 120; ++i) t.push_back(char('a' + (i * 11) % 26));
        tests.emplace_back(s, t);
    }

    // 9. Alternating characters
    {
        string s, t;
        for (int i = 0; i < 60; ++i) { s += "ab"; t += "ba"; } // length 120 each
        tests.emplace_back(s, t);
    }

    // 10. Digits repeated vs reversed digits repeated
    {
        string s, t;
        for (int i = 0; i < 10; ++i) s += "0123456789"; // length 100
        for (int i = 0; i < 8; ++i) t += "9876543210";  // length 80
        tests.emplace_back(s, t);
    }

    Solution sol;
    long long checksum = 0;

    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            checksum += sol.longestPalindrome(tc.first, tc.second);
        }
    }

    auto end = Clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time: " << elapsed << " ms\n";

    return 0;
}