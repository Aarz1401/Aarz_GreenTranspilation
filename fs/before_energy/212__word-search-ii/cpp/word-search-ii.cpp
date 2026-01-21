#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Time:  O(m * n * 4 * 3^(h - 1)) ~= O(m * n * 3^h), h is the height of trie
// Space: O(t), t is the number of nodes in trie

struct TrieNode {
    bool is_string;
    unordered_map<char, TrieNode*> leaves;
    TrieNode() : is_string(false) {}
    ~TrieNode() {
        for (auto& kv : leaves) {
            delete kv.second;
        }
    }
    // Inserts a word into the trie.
    void insert(const string& word) {
        TrieNode* cur = this;
        for (char c : word) {
            auto it = cur->leaves.find(c);
            if (it == cur->leaves.end()) {
                TrieNode* node = new TrieNode();
                cur->leaves[c] = node;
                cur = node;
            } else {
                cur = it->second;
            }
        }
        cur->is_string = true;
    }
};

class Solution {
public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        vector<string> ans;
        if (board.empty() || board[0].empty() || words.empty()) return ans;

        vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
        unordered_set<string> result;
        TrieNode trie;
        for (const auto& word : words) {
            trie.insert(word);
        }

        for (int i = 0; i < static_cast<int>(board.size()); ++i) {
            for (int j = 0; j < static_cast<int>(board[0].size()); ++j) {
                string cur_word;
                findWordsRecu(board, &trie, i, j, visited, cur_word, result);
            }
        }

        ans.reserve(result.size());
        for (const auto& s : result) ans.push_back(s);
        return ans;
    }

private:
    void findWordsRecu(const vector<vector<char>>& board,
                       TrieNode* trie,
                       int i,
                       int j,
                       vector<vector<bool>>& visited,
                       string& cur_word,
                       unordered_set<string>& result) {
        if (!trie || i < 0 || i >= static_cast<int>(board.size()) ||
            j < 0 || j >= static_cast<int>(board[0].size()) || visited[i][j]) {
            return;
        }

        auto it = trie->leaves.find(board[i][j]);
        if (it == trie->leaves.end()) {
            return;
        }

        cur_word.push_back(board[i][j]);
        TrieNode* next_node = it->second;
        if (next_node->is_string) {
            result.insert(cur_word);
        }

        visited[i][j] = true;
        findWordsRecu(board, next_node, i + 1, j, visited, cur_word, result);
        findWordsRecu(board, next_node, i - 1, j, visited, cur_word, result);
        findWordsRecu(board, next_node, i, j + 1, visited, cur_word, result);
        findWordsRecu(board, next_node, i, j - 1, visited, cur_word, result);
        visited[i][j] = false;
        cur_word.pop_back();
    }
};