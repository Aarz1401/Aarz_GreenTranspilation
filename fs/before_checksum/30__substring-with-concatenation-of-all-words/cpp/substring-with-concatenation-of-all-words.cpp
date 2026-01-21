#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;
using std::vector;

// Time:  O((m + n) * k), where m is string length, n is dictionary size, k is word length
// Space: O(n * k)
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.empty()) return result;

        int m = static_cast<int>(s.size());
        int n = static_cast<int>(words.size());
        int k = static_cast<int>(words[0].size());
        if (m < n * k) return result;

        unordered_map<string, int> lookup;
        for (const auto& w : words) {
            ++lookup[w]; // Space: O(n * k)
        }

        // Time: O(k)
        for (int i = 0; i < k; ++i) {
            int left = i, count = 0;
            unordered_map<string, int> tmp;
            // Time: O(m / k)
            for (int j = i; j <= m - k; j += k) {
                string s1 = s.substr(j, k); // Time: O(k)
                auto it = lookup.find(s1);
                if (it != lookup.end()) {
                    ++tmp[s1];
                    ++count;
                    while (tmp[s1] > it->second) {
                        string leftWord = s.substr(left, k);
                        --tmp[leftWord];
                        --count;
                        left += k;
                    }
                    if (count == n) {
                        result.push_back(left);
                    }
                } else {
                    tmp.clear();
                    count = 0;
                    left = j + k;
                }
            }
        }

        return result;
    }
};

// Time:  O(m * n * k), where m is string length, n is dictionary size, k is word length
// Space: O(n * k)
class Solution2 {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        int m = static_cast<int>(s.size());
        int n = static_cast<int>(words.size());
        if (n == 0) return result;
        int k = static_cast<int>(words[0].size());
        if (m < n * k) return result;

        unordered_map<string, int> lookup;
        for (const auto& w : words) {
            ++lookup[w]; // Space: O(n * k)
        }

        // Time: O(m)
        for (int i = 0; i <= m - k * n; ++i) {
            unordered_map<string, int> cur;
            int j = 0;
            // Time: O(n)
            while (j < n) {
                string word = s.substr(i + j * k, k); // Time: O(k)
                auto it = lookup.find(word);
                if (it == lookup.end()) {
                    break;
                }
                ++cur[word];
                if (cur[word] > it->second) {
                    break;
                }
                ++j;
            }
            if (j == n) {
                result.push_back(i);
            }
        }

        return result;
    }
};