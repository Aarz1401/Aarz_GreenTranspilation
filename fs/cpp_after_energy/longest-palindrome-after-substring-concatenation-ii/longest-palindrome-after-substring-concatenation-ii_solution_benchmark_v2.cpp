#include <string>
#include <vector>
#include <algorithm>
#include <utility>

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
    vector<pair<string, string>> tests = {
        {"a", "a"},
        {"abc", "def"},
        {"abc", "cba"},
        {"abccba", "abc"},
        {"abcdefg", "gfedcba"},
        {"aaaaaaa", "aaaa"},
        {"banana", "ananas"},
        {"abaxyzzyxf", "xyzz"},
        {"thequickbrownfox", "xofnworbkciuqeht"},
        {"palindromeemordnilap", "levelrotor"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            int r = sol.longestPalindrome(tc.first, tc.second);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}