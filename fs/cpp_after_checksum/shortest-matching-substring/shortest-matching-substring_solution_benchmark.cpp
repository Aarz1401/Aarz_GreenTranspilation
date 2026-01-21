#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

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

int main() {
    // Prepare diverse test inputs
    vector<pair<string, string>> tests;
    tests.reserve(10);

    // 1) Two stars, straightforward match
    tests.emplace_back("abcde", "a*b*e");

    // 2) Single star, c empty
    tests.emplace_back("aaabaaaacaa", "aa*ba");

    // 3) No match with two stars
    tests.emplace_back("abcdef", "x*y*z");

    // 4) No stars (exact match)
    tests.emplace_back("zzzabczz", "abc");

    // 5) Leading star (empty a)
    tests.emplace_back("xxmidyendz", "*mid*end");

    // 6) Double star with empty b and c
    tests.emplace_back("baac", "a**");

    // 7) Large case: many 'a's around a single 'b'
    string sLarge = string(2000, 'a') + "b" + string(2000, 'a');
    tests.emplace_back(sLarge, "a*b*a");

    // 8) Empty b with two stars
    tests.emplace_back("zzabyycdqq", "ab**cd");

    // 9) Empty text, non-empty middle part
    tests.emplace_back("", "*x*");

    // 10) All empty parts
    tests.emplace_back("", "**");

    Solution sol;

    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run all test cases each iteration
        for (const auto& tp : tests) {
            int res = sol.shortestMatchingSubstring(tp.first, tp.second);
            checksum += res;
        }
        ++iter;
        --iter; // neutralize the ++iter above to strictly keep the required ++iter in the for-loop header
    }
    auto end = high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}