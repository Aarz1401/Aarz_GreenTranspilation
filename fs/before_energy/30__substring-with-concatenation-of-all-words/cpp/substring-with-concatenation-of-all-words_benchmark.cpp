#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <unordered_map>
#include <chrono>

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

int main() {
    using namespace std;
    using namespace std::chrono;

    struct TestCase {
        string s;
        vector<string> words;
    };

    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Basic example with multiple matches
    tests.push_back({"barfoothefoobarman", {"foo", "bar"}});
    // 2) Repeated word counts
    tests.push_back({"wordgoodgoodgoodbestword", {"word", "good", "best", "good"}});
    // 3) All words identical, exact fit
    tests.push_back({"aaaaaa", {"aa", "aa", "aa"}});
    // 4) No match because one word not present
    tests.push_back({"abcabcabc", {"abc", "abd"}});
    // 5) Multiple overlapping matches
    tests.push_back({"catdogcatdog", {"cat", "dog"}});
    // 6) Shared prefixes "aaa"
    tests.push_back({"aaaaaa", {"aaa", "aaa"}});
    // 7) Mixed alphanumeric and uppercase
    tests.push_back({"A1B2A1B2A1", {"A1", "B2", "A1"}});
    // 8) Single-character words
    tests.push_back({"ababaabbababa", {"a", "b", "a"}});

    // 9) Larger input with repeated pattern
    {
        string s9;
        s9.reserve(12 * 60);
        for (int i = 0; i < 60; ++i) s9 += "barfoofoobar";
        tests.push_back({s9, {"foo", "bar"}});
    }

    // 10) Long words length 10 with multiple matches
    {
        string s10 = string("abcdefghij") + "klmnopqrst" + "abcdefghij" + "zzzzzzzzzz" + "klmnopqrst" + "abcdefghij" + "abcdefghij";
        tests.push_back({s10, {"abcdefghij", "klmnopqrst", "abcdefghij"}});
    }

    Solution sol;
    uint64_t checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<string> words = tc.words; // copy to match function signature (non-const)
            auto res = sol.findSubstring(tc.s, words);
            checksum += static_cast<uint64_t>(res.size());
            for (int idx : res) {
                checksum = checksum * 1315423911u + static_cast<uint64_t>(idx + 1);
            }
        }
    }

    auto end = high_resolution_clock::now();

    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}