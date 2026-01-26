#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

class Solution {
public:
    std::vector<std::string> wordBreak(const std::string& s, std::vector<std::string>& wordDict) {
        int n = static_cast<int>(s.size());
        std::unordered_set<std::string> dict(wordDict.begin(), wordDict.end());

        int max_len = 0;
        for (const auto& w : wordDict) {
            max_len = std::max(max_len, static_cast<int>(w.size()));
        }

        std::vector<bool> can_break(n + 1, false);
        std::vector<std::vector<bool>> valid(n, std::vector<bool>(n, false));
        can_break[0] = true;

        for (int i = 1; i <= n; ++i) {
            for (int l = 1; l <= std::min(i, max_len); ++l) {
                if (can_break[i - l]) {
                    if (dict.find(s.substr(i - l, l)) != dict.end()) {
                        valid[i - l][i - 1] = true;
                        can_break[i] = true;
                    }
                }
            }
        }

        std::vector<std::string> result;
        if (can_break[n]) {
            std::vector<std::string> path;
            wordBreakHelper(s, valid, 0, path, result);
        }
        return result;
    }

private:
    void wordBreakHelper(const std::string& s,
                         const std::vector<std::vector<bool>>& valid,
                         int start,
                         std::vector<std::string>& path,
                         std::vector<std::string>& result) {
        if (start == static_cast<int>(s.size())) {
            result.push_back(join(path));
            return;
        }
        for (int i = start; i < static_cast<int>(s.size()); ++i) {
            if (valid[start][i]) {
                path.push_back(s.substr(start, i - start + 1));
                wordBreakHelper(s, valid, i + 1, path, result);
                path.pop_back();
            }
        }
    }

    std::string join(const std::vector<std::string>& parts) {
        std::string res;
        for (size_t i = 0; i < parts.size(); ++i) {
            if (i) res.push_back(' ');
            res += parts[i];
        }
        return res;
    }
};

struct Test {
    std::string s;
    std::vector<std::string> dict;
};

int main() {
    std::vector<Test> tests = {
        {"catsanddog", {"cat","cats","and","sand","dog"}},
        {"pineapplepenapple", {"apple","pen","applepen","pine","pineapple"}},
        {"aaaaaaa", {"a","aa","aaa"}},
        {"leetcode", {"leet","code"}},
        {"catsandog", {"cats","dog","sand","and","cat"}},
        {"abcd", {"a","abc","b","cd"}},
        {"aaaaab", {"a","aa","aaa","aaaa","b"}},
        {"bb", {"a","b","bbb","bbbb"}},
        {"foobarbaz", {"foo","bar","baz","foobar","barbaz","foob","arb","az"}},
        {"impossible", {"im","possible","impo","ss","ible"}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            auto res = sol.wordBreak(t.s, t.dict);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}