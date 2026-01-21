#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <chrono>
#include <cstdint>

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
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Classic example
    tests.push_back({
        {
            {'o','a','a','n'},
            {'e','t','a','e'},
            {'i','h','k','r'},
            {'i','f','l','v'}
        },
        {"oath","pea","eat","rain"}
    });

    // 2) Small 2x2 with overlapping candidates
    tests.push_back({
        {
            {'a','b'},
            {'c','d'}
        },
        {"ab","abc","abcd","acdb","bd","cd","adcb"}
    });

    // 3) Empty board
    tests.push_back({
        {
        },
        {"a","b"}
    });

    // 4) Empty words
    tests.push_back({
        {
            {'a','b'},
            {'c','d'}
        },
        { }
    });

    // 5) Single cell
    tests.push_back({
        {
            {'a'}
        },
        {"a","aa","b"}
    });

    // 6) Larger 5x5 mixed letters
    tests.push_back({
        {
            {'t','h','i','s','a'},
            {'w','a','t','s','o'},
            {'o','a','h','g','g'},
            {'f','g','d','t','e'},
            {'x','y','z','b','n'}
        },
        {"this","two","fat","that","hat","wag","dog","goat","fog","than","gadget"}
    });

    // 7) No matches
    tests.push_back({
        {
            {'x','y','z'},
            {'x','y','z'},
            {'x','y','z'}
        },
        {"abc","def","ghi"}
    });

    // 8) All same letters with duplicates in words
    tests.push_back({
        {
            {'a','a','a'},
            {'a','a','a'},
            {'a','a','a'}
        },
        {"a","aa","aaa","aaaa","aaaaa","aaaaaa","a"}
    });

    // 9) Rectangular 3x5
    tests.push_back({
        {
            {'s','e','e','n','e'},
            {'l','e','e','k','s'},
            {'a','b','a','b','a'}
        },
        {"see","seen","seek","seeks","leek","leeks","seab","eel","ababa"}
    });

    // 10) 4x6 keyboard-like layout
    tests.push_back({
        {
            {'q','w','e','r','t','y'},
            {'a','s','d','f','g','h'},
            {'z','x','c','v','b','n'},
            {'m','j','k','l','p','o'}
        },
        {"qwerty","asdf","zxcv","mjk","klp","qwe","ghn","bnm","pol","tygh","cvbn","sdg","jkl","poi"}
    });

    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            Solution sol;
            auto res = sol.findWords(tc.board, tc.words);
            for (const auto& s : res) {
                uint64_t local = 1469598103934665603ULL; // FNV-1a
                for (unsigned char c : s) {
                    local ^= c;
                    local *= 1099511628211ULL;
                }
                checksum ^= (local + static_cast<uint64_t>(s.size()) * 1315423911ULL);
            }
            checksum += static_cast<uint64_t>(res.size() * 2654435761U);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed(ms): " << elapsed_ms << "\n";

    return 0;
}