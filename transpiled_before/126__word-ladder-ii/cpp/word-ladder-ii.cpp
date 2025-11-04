#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> words(wordList.begin(), wordList.end());
        vector<vector<string>> result;
        if (!words.count(endWord)) {
            return result;
        }

        unordered_map<string, unordered_set<string>> tree;
        unordered_set<string> left{beginWord}, right{endWord};
        bool is_reversed = false;
        bool is_found = false;
        int L = static_cast<int>(beginWord.size());

        while (!left.empty()) {
            for (const auto& w : left) {
                words.erase(w);
            }
            unordered_set<string> new_left;

            for (const auto& word : left) {
                string curr = word;
                for (int i = 0; i < L; ++i) {
                    char original = curr[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == original) continue;
                        curr[i] = c;
                        const string& new_word = curr;
                        if (!words.count(new_word)) {
                            continue;
                        }
                        if (right.count(new_word)) {
                            is_found = true;
                        } else {
                            new_left.insert(new_word);
                        }
                        if (!is_reversed) {
                            tree[new_word].insert(word);
                        } else {
                            tree[word].insert(new_word);
                        }
                    }
                    curr[i] = original;
                }
            }
            if (is_found) break;
            left = std::move(new_left);
            if (left.size() > right.size()) {
                swap(left, right);
                is_reversed = !is_reversed;
            }
        }

        if (!is_found) {
            return result;
        }

        vector<string> path;
        backtracking(tree, beginWord, endWord, path, result);
        return result;
    }

private:
    void backtracking(const unordered_map<string, unordered_set<string>>& tree,
                      const string& beginWord,
                      const string& word,
                      vector<string>& path,
                      vector<vector<string>>& result) {
        if (word == beginWord) {
            vector<string> tmp = path;
            tmp.push_back(beginWord);
            reverse(tmp.begin(), tmp.end());
            result.push_back(std::move(tmp));
            return;
        }
        auto it = tree.find(word);
        if (it == tree.end()) return;

        path.push_back(word);
        for (const auto& prev : it->second) {
            backtracking(tree, beginWord, prev, path, result);
        }
        path.pop_back();
    }
};