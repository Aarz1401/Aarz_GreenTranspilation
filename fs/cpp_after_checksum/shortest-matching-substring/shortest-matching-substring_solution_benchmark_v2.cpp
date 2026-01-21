#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
using namespace std;

// Time:  O(n + m)
// Space: O(n + m)
// kmp, two pointers (three pointers)
class Solution {
public:
    int shortestMatchingSubstring(string s, string p) {
        auto splitByStar = [](const string& str) -> vector<string> {
            vector<string> parts;
            string cur;
            for (char ch : str) {
                if (ch == '*') {
                    parts.push_back(cur);
                    cur.clear();
                } else {
                    cur.push_back(ch);
                }
            }
            parts.push_back(cur);
            return parts;
        };

        auto getPrefix = [&](const string& pattern) -> vector<int> {
            int n = static_cast<int>(pattern.size());
            vector<int> prefix(n, -1);
            int j = -1;
            for (int i = 1; i < n; ++i) {
                while (j + 1 > 0 && pattern[j + 1] != pattern[i]) {
                    j = prefix[j];
                }
                if (pattern[j + 1] == pattern[i]) {
                    ++j;
                }
                prefix[i] = j;
            }
            return prefix;
        };

        auto KMP = [&](const string& text, const string& pattern) -> vector<int> {
            vector<int> res;
            if (pattern.empty()) {
                for (int i = 0; i <= static_cast<int>(text.size()); ++i) {
                    res.push_back(i);
                }
                return res;
            }
            vector<int> prefix = getPrefix(pattern);
            int j = -1;
            for (int i = 0; i < static_cast<int>(text.size()); ++i) {
                while (j + 1 > 0 && pattern[j + 1] != text[i]) {
                    j = prefix[j];
                }
                if (pattern[j + 1] == text[i]) {
                    ++j;
                }
                if (j + 1 == static_cast<int>(pattern.size())) {
                    res.push_back(i - j);
                    j = prefix[j];
                }
            }
            return res;
        };

        vector<string> parts = splitByStar(p);
        // Expect exactly three parts: a, b, c
        string a = parts.size() > 0 ? parts[0] : string();
        string b = parts.size() > 1 ? parts[1] : string();
        string c = parts.size() > 2 ? parts[2] : string();

        int n = static_cast<int>(s.size());
        int la = static_cast<int>(a.size());
        int lb = static_cast<int>(b.size());
        int lc = static_cast<int>(c.size());

        vector<int> occA = KMP(s, a);
        vector<int> occB = KMP(s, b);
        vector<int> occC = KMP(s, c);

        int result = INT_MAX;
        int idxB = 0, idxC = 0;

        for (int iIdx = 0; iIdx < static_cast<int>(occA.size()); ++iIdx) {
            int i = occA[iIdx];
            while (idxB < static_cast<int>(occB.size()) && occB[idxB] < i + la) {
                ++idxB;
            }
            if (idxB == static_cast<int>(occB.size())) {
                break;
            }
            while (idxC < static_cast<int>(occC.size()) && occC[idxC] < occB[idxB] + lb) {
                ++idxC;
            }
            if (idxC == static_cast<int>(occC.size())) {
                break;
            }
            result = min(result, (occC[idxC] + lc) - i);
        }

        return result == INT_MAX ? -1 : result;
    }
};

struct Test {
    string s;
    string p;
};

int main() {
    vector<Test> tests = {
        {"abcde", "a*b*e"},
        {"aaabbbccc", "a*b*c"},
        {"xxabyybczzc", "ab*bc*c"},
        {"ababababa", "aba*bab*aba"},
        {"thequickbrownfoxjumpsoverthelazydog", "the*own*dog"},
        {"aaaaabaaaaacaaaaad", "aaa*ba*ad"},
        {"cabxxabcxxabcc", "ca*ab*cc"},
        {"mississippi", "mi*si*pi"},
        {"xyzxyzxyz", "xy*zz*yz"},
        {"aaabaaaaaccc", "aaab*aaaa*cc"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.shortestMatchingSubstring(t.s, t.p);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}