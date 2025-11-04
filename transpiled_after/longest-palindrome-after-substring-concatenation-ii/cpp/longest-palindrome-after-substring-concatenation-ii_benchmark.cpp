#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono>

using namespace std;

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

struct Test {
    string first;
    string second;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Test> tests = {
        {"", ""},            // both empty
        {"a", "a"},          // single identical character
        {"a", "b"},          // single different character
        {"ab", "ba"},        // possible cross-boundary palindrome "abba"
        {"aaa", "aaa"},      // repeated characters
        {"abc", "def"},      // disjoint characters
        {"race", "car"},     // classic "racecar"
        {"abba", "abba"},    // palindromic segments
        {"abcba", "xyz"},    // palindrome in s
        {"xyz", "abcba"}     // palindrome in t
    };

    Solution sol;
    const int iterations = 1000;
    long long total = 0;

    auto start = chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            total += sol.longestPalindrome(tc.first, tc.second);
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Total result: " << total << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}