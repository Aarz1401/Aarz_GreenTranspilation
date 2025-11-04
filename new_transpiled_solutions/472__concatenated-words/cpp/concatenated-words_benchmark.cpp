#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <chrono>
#include <cstdint>

using namespace std;

class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        unordered_set<string> lookup(words.begin(), words.end());
        vector<string> result;
        result.reserve(words.size());
        for (const auto& word : words) {
            int n = static_cast<int>(word.size());
            vector<char> dp(n + 1, false);
            dp[0] = true;
            for (int i = 0; i < n; ++i) {
                if (!dp[i]) continue;
                for (int j = i + 1; j <= n; ++j) {
                    if (j - i < n && lookup.find(word.substr(i, j - i)) != lookup.end()) {
                        dp[j] = true;
                    }
                }
                if (dp[n]) {
                    result.emplace_back(word);
                    break;
                }
            }
        }
        return result;
    }
};

int main() {
    // Prepare 10 diverse test inputs
    vector<vector<string>> tests;
    tests.reserve(10);

    // 1) Classic concatenation cases
    tests.push_back({"cat","cats","catsdogcats","dog","dogcatsdog","hippopotamuses","rat","ratcatdogcat"});

    // 2) No concatenations
    tests.push_back({"xyz","abc","defgh","ijkl","mnop"});

    // 3) Duplicates and simple concatenations
    tests.push_back({"cat","catcat","catcat","catcatcat","dog","dogcat","catdog","dogdogcat"});

    // 4) Includes empty string and small repeats
    tests.push_back({"","a","aa","aaa","aaaa","b","bb","bbb"});

    // 5) Prefix/suffix style words
    tests.push_back({"base","ball","baseball","ballbase","basebase","ballball"});

    // 6) Overlapping but mostly non-concatenatable
    tests.push_back({"abcde","bcdea","cdeab","deabc","eabcd","abcdabc"});

    // 7) Long chain with one large repeat and a small valid one
    tests.push_back({"a","b","ab","abc","abcd","abcde","abcdef","abcdefg","abcdefgh","abcdefghi","abcdefghij","abcdefghijabcdefghij"});

    // 8) Palindromic patterns and combinations
    tests.push_back({"noon","good","goodnoon","noongood","goodgood","nogood","on"});

    // 9) Programmatically generated repeated character strings
    vector<string> t9;
    t9.push_back("x");
    t9.push_back("xx");
    t9.push_back("xxx");
    t9.push_back(string(8, 'x'));   // 8 x's
    t9.push_back(string(16, 'x'));  // 16 x's = 8 + 8
    t9.push_back(string(24, 'x'));  // 24 x's = 8 + 8 + 8
    tests.push_back(std::move(t9));

    // 10) Color words with multi-part concatenations
    tests.push_back({"red","blue","green","redblue","bluegreen","redbluegreen","greenredblue","blueredgreenred","redred"});

    if (tests.size() != 10) {
        cerr << "Error: Expected 10 test inputs, got " << tests.size() << endl;
        return 1;
    }

    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        Solution sol;
        for (const auto& tc : tests) {
            // Create a modifiable copy for the function signature (non-const reference)
            vector<string> words = tc;
            auto res = sol.findAllConcatenatedWordsInADict(words);
            checksum += static_cast<uint64_t>(res.size());
            for (const auto& s : res) {
                checksum += static_cast<uint64_t>(s.size());
                if (!s.empty()) {
                    checksum += static_cast<uint64_t>(static_cast<unsigned char>(s.front()));
                    checksum += static_cast<uint64_t>(static_cast<unsigned char>(s.back()));
                }
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed microseconds: " << elapsed_us << "\n";
    return 0;
}