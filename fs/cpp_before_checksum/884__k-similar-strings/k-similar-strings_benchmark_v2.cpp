#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <utility>

class Solution {
public:
    int kSimilarity(std::string A, std::string B) {
        auto neighbors = [&](const std::string& s) -> std::vector<std::string> {
            int i = 0, n = static_cast<int>(s.size());
            for (; i < n; ++i) {
                if (s[i] != B[i]) break;
            }
            std::vector<std::string> res;
            if (i == n) return res;
            std::string t = s;
            for (int j = i + 1; j < n; ++j) {
                if (t[j] == B[i]) {
                    std::swap(t[i], t[j]);
                    res.emplace_back(t);
                    std::swap(t[j], t[i]);
                }
            }
            return res;
        };

        std::queue<std::string> q;
        q.push(A);
        std::unordered_set<std::string> lookup;
        int result = 0;

        while (!q.empty()) {
            int sz = static_cast<int>(q.size());
            for (int _ = 0; _ < sz; ++_) {
                std::string s = q.front(); q.pop();
                if (s == B) {
                    return result;
                }
                for (const auto& t : neighbors(s)) {
                    if (!lookup.count(t)) {
                        lookup.insert(t);
                        q.push(t);
                    }
                }
            }
            ++result;
        }
        return result;
    }
};

int main() {
    std::vector<std::pair<std::string, std::string>> tests = {
        {"a", "a"},
        {"ab", "ba"},
        {"abc", "bca"},
        {"aabc", "abca"},
        {"abac", "baca"},
        {"aabbcc", "abcabc"},
        {"abcdef", "fabcde"},
        {"abcdef", "badcfe"},
        {"abababab", "babababa"},
        {"aaabbbccdd", "ddccbbaaab"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& p : tests) {
            checksum += sol.kSimilarity(p.first, p.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}