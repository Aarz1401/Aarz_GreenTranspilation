#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <string>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    std::string nearestPalindromic(std::string n) {
        const int l = static_cast<int>(n.size());
        bool isOdd = (l % 2 == 1);

        std::unordered_set<std::string> candidates;

        // Candidate: 10^l + 1 => "1" + (l-1)*"0" + "1"
        std::string high = "1";
        if (l > 0) high += std::string(l - 1, '0');
        high += "1";
        candidates.insert(high);

        // Candidate: 10^(l-1) - 1 => for l==1: "0", else (l-1)*"9"
        std::string low;
        if (l == 1) {
            low = "0";
        } else {
            low = std::string(l - 1, '9');
        }
        candidates.insert(low);

        std::string prefix = n.substr(0, (l + 1) / 2);
        std::string p0 = decStr(prefix);
        std::string p1 = prefix;
        std::string p2 = incStr(prefix);

        for (const std::string& p : {p0, p1, p2}) {
            std::string pal = makePal(p, isOdd);
            pal = normalize(pal);
            candidates.insert(pal);
        }

        // Exclude the number itself if present
        candidates.erase(n);

        std::string best;
        for (const auto& cand : candidates) {
            if (cand == n || cand.empty()) continue;
            if (best.empty() || isBetter(cand, best, n)) {
                best = cand;
            }
        }
        return best;
    }

private:
    static std::string normalize(const std::string& s) {
        size_t i = 0;
        while (i < s.size() && s[i] == '0') ++i;
        if (i == s.size()) return "0";
        return s.substr(i);
    }

    static std::string makePal(const std::string& s, bool isOdd) {
        std::string rev = s;
        if (isOdd && !rev.empty()) {
            rev.pop_back();
        }
        std::reverse(rev.begin(), rev.end());
        return s + rev;
    }

    static std::string incStr(std::string s) {
        for (int i = static_cast<int>(s.size()) - 1; i >= 0; --i) {
            if (s[i] < '9') {
                s[i]++;
                return s;
            }
            s[i] = '0';
        }
        s.insert(s.begin(), '1');
        return s;
    }

    static std::string decStr(std::string s) {
        // Assume s represents a non-negative integer.
        // If s is "0", return "0".
        if (s == "0") return "0";
        int i = static_cast<int>(s.size()) - 1;
        while (i >= 0 && s[i] == '0') {
            s[i] = '9';
            --i;
        }
        if (i >= 0) {
            s[i]--;
        }
        // Remove leading zeros
        return normalize(s);
    }

    static int cmpNum(const std::string& a, const std::string& b) {
        std::string an = normalize(a);
        std::string bn = normalize(b);
        if (an.size() != bn.size()) {
            return (an.size() < bn.size()) ? -1 : 1;
        }
        if (an == bn) return 0;
        return (an < bn) ? -1 : 1;
    }

    static std::string subNonNeg(const std::string& a, const std::string& b) {
        // Precondition: a >= b, both non-negative numeric strings
        int i = static_cast<int>(a.size()) - 1;
        int j = static_cast<int>(b.size()) - 1;
        int borrow = 0;
        std::string res;
        while (i >= 0 || j >= 0) {
            int da = (i >= 0) ? (a[i] - '0') : 0;
            int db = (j >= 0) ? (b[j] - '0') : 0;
            int diff = da - borrow - db;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            } else {
                borrow = 0;
            }
            res.push_back(static_cast<char>('0' + diff));
            --i; --j;
        }
        while (res.size() > 1 && res.back() == '0') res.pop_back();
        std::reverse(res.begin(), res.end());
        return normalize(res);
    }

    static std::string absDiff(const std::string& a, const std::string& b) {
        int c = cmpNum(a, b);
        if (c == 0) return "0";
        if (c > 0) {
            return subNonNeg(a, b);
        } else {
            return subNonNeg(b, a);
        }
    }

    static bool isBetter(const std::string& a, const std::string& b, const std::string& n) {
        std::string da = absDiff(a, n);
        std::string db = absDiff(b, n);
        int cmpd = cmpNum(da, db);
        if (cmpd != 0) return cmpd < 0;
        // Tie-breaker: smaller numeric value
        return cmpNum(a, b) < 0;
    }
};