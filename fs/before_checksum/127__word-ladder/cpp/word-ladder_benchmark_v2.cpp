#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <utility>
#include <cstddef>

using namespace std;

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

// Time:  O(b^d), b is the branch factor of bfs, d is the result depth
// Space: O(w * l), w is the number of words, l is the max length of words
// class Solution2 {
// public:
//     int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
//         unordered_set<string> lookup(wordList.begin(), wordList.end());
//         if (!lookup.count(endWord)) {
//             return 0;
//         }
//         int ladder = 2;
//         vector<string> q{beginWord};
//         const size_t L = beginWord.size();
//         while (!q.empty()) {
//             vector<string> new_q;
//             for (const string& word : q) {
//                 string cur = word;
//                 for (size_t i = 0; i < L; ++i) {
//                     char orig = cur[i];
//                     for (char c = 'a'; c <= 'z'; ++c) {
//                         if (c == orig) continue;
//                         cur[i] = c;
//                         if (cur == endWord) {
//                             return ladder;
//                         }
//                         if (lookup.count(cur)) {
//                             lookup.erase(cur);
//                             new_q.push_back(cur);
//                         }
//                         cur[i] = orig;
//                     }
//                 }
//             }
//             q = std::move(new_q);
//             ++ladder;
//         }
//         return 0;
//     }
// };

struct TestCase {
    string begin;
    string end;
    vector<string> wordList;
};

int main() {
    vector<TestCase> tests = {
        {"hit", "cog", {"hot","dot","dog","lot","log","cog"}},
        {"hit", "cog", {"hot","dot","dog","lot","log"}},
        {"aab", "abb", {"abb","aba","bbb"}},
        {"lead", "gold", {"load","goad","gold","golf","gald"}},
        {"lost", "cost", {"most","host","cost","lost","lose"}},
        {"abc", "xyz", {"xbc","xyc","xyz","xya","abx"}},
        {"aaaa", "bbbb", {"baaa","bbaa","bbba","bbbb","abaa"}},
        {"talk", "tail", {"tall","tail","balk","tark","tauk"}},
        {"abcd", "dcba", {"abce","abde","acde","bcde","dcba"}},
        {"aaaaa", "zzzzz", {"zaaaa","zzaaa","zzzaa","zzzza","zzzzz","aaaaz"}}
    };

    volatile int sink = 0;
    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.ladderLength(tests[i].begin, tests[i].end, tests[i].wordList);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}