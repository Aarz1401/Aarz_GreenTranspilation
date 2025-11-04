#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include <cstddef>
#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Time:  O(b^(d/2)), b is the branch factor of bfs, d is the result depth
// Space: O(w * l), w is the number of words, l is the max length of words

// two-end bfs
class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        if (!words.count(endWord)) {
            return 0;
        }

        unordered_set<string> left{beginWord};
        unordered_set<string> right{endWord};
        int ladder = 2;
        const size_t L = beginWord.size();

        while (!left.empty()) {
            for (const auto& w : left) {
                words.erase(w);
            }
            unordered_set<string> new_left;

            for (const string& word : left) {
                string cur = word;
                for (size_t i = 0; i < L; ++i) {
                    char orig = cur[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == orig) continue;
                        cur[i] = c;
                        if (!words.count(cur)) {
                            cur[i] = orig;
                            continue;
                        }
                        if (right.count(cur)) {
                            return ladder;
                        }
                        new_left.insert(cur);
                        cur[i] = orig;
                    }
                }
            }

            left = std::move(new_left);
            ++ladder;
            if (left.size() > right.size()) {
                std::swap(left, right);
            }
        }
        return 0;
    }
};

struct TestCase {
    string beginWord;
    string endWord;
    vector<string> wordList;
};

int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    // Test 1: Standard case with known path length 5
    tests.push_back(TestCase{
        "hit", "cog",
        {"hot","dot","dog","lot","log","cog"}
    });

    // Test 2: End word not in list -> 0
    tests.push_back(TestCase{
        "hit", "cog",
        {"hot","dot","dog","lot","log"}
    });

    // Test 3: Single-letter words, minimal path length 2
    tests.push_back(TestCase{
        "a", "c",
        {"a","b","c"}
    });

    // Test 4: Multiple valid paths, short chain
    tests.push_back(TestCase{
        "talk", "tail",
        {"talk","tall","tail","balk","tale","fail"}
    });

    // Test 5: Classic lead->gold transformation of length 4
    tests.push_back(TestCase{
        "lead", "gold",
        {"load","goad","gold","golf","gale","geld","lead"}
    });

    // Test 6: Longer chain across 4-letter words
    tests.push_back(TestCase{
        "aaaa", "bbbb",
        {"aaab","aabb","abbb","bbbb","baaa","bbaa"}
    });

    // Test 7: Simple 2-step transformation
    tests.push_back(TestCase{
        "lost", "cost",
        {"lost","cost","most","host","post"}
    });

    // Test 8: No path even though end is present
    tests.push_back(TestCase{
        "abc", "xyz",
        {"abx","axc","xbc","yzz","xya","xyz"}
    });

    // Test 9: Direct neighbor at the end (length 4 words)
    tests.push_back(TestCase{
        "zzzz", "zzzy",
        {"zzzy","zzyy","zyyy","yyyy","zzzz","azzz","zzzq","zzqy"}
    });

    // Test 10: Dense 3-letter space with {'a','b','c'} allowing a path from aaa to ccc
    {
        vector<string> dense;
        dense.reserve(27);
        for (char c1 = 'a'; c1 <= 'c'; ++c1) {
            for (char c2 = 'a'; c2 <= 'c'; ++c2) {
                for (char c3 = 'a'; c3 <= 'c'; ++c3) {
                    string s;
                    s.push_back(c1);
                    s.push_back(c2);
                    s.push_back(c3);
                    dense.push_back(s);
                }
            }
        }
        tests.push_back(TestCase{"aaa", "ccc", dense});
    }

    volatile long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        Solution sol;
        for (size_t i = 0; i < tests.size(); ++i) {
            int res = sol.ladderLength(tests[i].beginWord, tests[i].endWord, tests[i].wordList);
            checksum += res;
        }
    }

    auto end = high_resolution_clock::now();
    auto us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << us << "\n";

    return 0;
}