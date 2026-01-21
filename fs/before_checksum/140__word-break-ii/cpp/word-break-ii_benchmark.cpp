#include <iostream>
#include <chrono>
#include <cstdint>
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

int main() {
    // Define 10 diverse test inputs
    std::vector<std::pair<std::string, std::vector<std::string>>> tests;
    tests.push_back({"catsanddog", {"cat","cats","and","sand","dog"}});
    tests.push_back({"pineapplepenapple", {"apple","pen","applepen","pine","pineapple"}});
    tests.push_back({"aaaaaaaa", {"a","aa","aaa","aaaa"}});
    tests.push_back({"leetcode", {"leet","code"}});
    tests.push_back({"catsandog", {"cats","dog","sand","and","cat"}});
    tests.push_back({"bb", {"a","b","bb","bbb"}});
    tests.push_back({"abcdabcdabcd", {"ab","abc","cd","abcd","d","cda","bca"}});
    tests.push_back({"aaaaab", {"a","aa","aaa","aaaa","aaaaa"}});
    tests.push_back({"catscatscats", {"cat","cats","scat","s","catsc","ats","ca","ts","atsc","at","t","c"}});
    tests.push_back({"thequickbrownfox", {"the","quick","brown","fox","thequick","quickbrown","brownfox"}});

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            auto res = sol.wordBreak(t.first, t.second);
            checksum += static_cast<uint64_t>(res.size());
            for (const auto& sentence : res) {
                checksum += static_cast<uint64_t>(sentence.size());
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}