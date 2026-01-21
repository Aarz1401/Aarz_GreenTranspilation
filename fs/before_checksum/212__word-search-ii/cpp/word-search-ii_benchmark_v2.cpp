#include <iostream>
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

struct TestCase {
    vector<vector<char>> board;
    vector<string> words;
};

int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    tests.push_back(TestCase{
        {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        },
        {"oath","pea","eat","rain","hklf","hf"}
    });

    tests.push_back(TestCase{
        {
            {'a','b','c','d','e','f'}
        },
        {"abc","cde","fed","abf","ace"}
    });

    tests.push_back(TestCase{
        {
            {'g'},
            {'h'},
            {'i'},
            {'j'},
            {'k'}
        },
        {"ghi","ijk","ghij","hg","jk"}
    });

    tests.push_back(TestCase{
        {
            {'a','a','a'},
            {'a','a','a'},
            {'a','a','a'}
        },
        {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa"}
    });

    tests.push_back(TestCase{
        {
            {'x','y','z'},
            {'p','q','r'},
            {'l','m','n'}
        },
        {"abc","def","ghi","uvw","rst"}
    });

    tests.push_back(TestCase{
        {
            {'s','e','e','d'},
            {'s','e','n','d'},
            {'s','e','e','d'}
        },
        {"see","seen","seed","sees","send","ends"}
    });

    tests.push_back(TestCase{
        {
            {'t','h','i','s','i','s','a'},
            {'s','i','m','p','l','e','x'}
        },
        {"this","is","a","simple","isth","xis","thisis","plex","simplex"}
    });

    tests.push_back(TestCase{
        {
            {'a','b','c','d'},
            {'e','f','g','h'},
            {'i','j','k','l'},
            {'m','n','o','p'}
        },
        {"abfj","mnop","aeim","cfk","ghkl"}
    });

    tests.push_back(TestCase{
        {
            {'a','b','a'},
            {'b','a','b'},
            {'a','b','a'}
        },
        {"aba","bab","ababa","babab","aaaa","abba"}
    });

    tests.push_back(TestCase{
        {
            {'l','e','e','t','c'},
            {'o','d','e','c','o'},
            {'d','e','l','e','t'},
            {'c','o','e','d','e'},
            {'c','o','d','e','s'}
        },
        {"leet","code","codes","leetcode","cool","deco","decode"}
    });

    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (auto& tc : tests) {
            auto res = sol.findWords(tc.board, tc.words);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}