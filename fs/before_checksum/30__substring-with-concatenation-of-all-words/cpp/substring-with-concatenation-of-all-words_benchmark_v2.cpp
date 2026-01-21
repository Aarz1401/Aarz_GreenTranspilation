#include <iostream>
#include <string>
#include <vector>
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

struct Test {
    string s;
    vector<string> words;
};

int main() {
    vector<Test> tests = {
        {"barfoothefoobarman", {"foo", "bar"}},
        {"wordgoodgoodgoodbestword", {"word", "good", "best", "word"}},
        {"barfoofoobarthefoobarman", {"bar", "foo", "the"}},
        {"lingmindraboofooowingdingbarrwingmonkeypoundcake", {"fooo", "barr", "wing", "ding", "wing"}},
        {"aaaaaa", {"aa", "aa", "aa"}},
        {"abababab", {"ab", "ba", "ab"}},
        {"abcabcabc", {"a", "b", "c"}},
        {"catcatdogcatdog", {"cat", "dog", "cat"}},
        {"short", {"longg", "words"}},
        {"foobarfoobar", {"foo", "bar", "foo"}}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<int> r = sol.findSubstring(t.s, const_cast<vector<string>&>(t.words));
            checksum += static_cast<int>(r.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}