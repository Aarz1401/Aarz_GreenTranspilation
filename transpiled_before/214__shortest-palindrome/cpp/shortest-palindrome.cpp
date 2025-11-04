#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Time:  O(n)
// Space: O(n)

// optimized from Solution2
class Solution {
public:
    string shortestPalindrome(string s) {
        // KMP prefix function variant returning longest prefix-suffix index for each position
        auto getPrefix = [](const string& pattern) {
            vector<int> prefix(pattern.size(), -1);
            int j = -1;
            for (size_t i = 1; i < pattern.size(); ++i) {
                while (j > -1 && pattern[j + 1] != pattern[i]) {
                    j = prefix[j];
                }
                if (pattern[j + 1] == pattern[i]) {
                    ++j;
                }
                prefix[i] = j;
            }
            return prefix;
        };

        if (s.empty()) {
            return s;
        }

        string rev(s.rbegin(), s.rend());
        string A = s + "#" + rev;
        vector<int> prefix = getPrefix(A);
        int last = prefix.back();  // index of last matched character in the longest prefix

        string suffix = s.substr(last + 1);
        reverse(suffix.begin(), suffix.end());
        return suffix + s;
    }
};