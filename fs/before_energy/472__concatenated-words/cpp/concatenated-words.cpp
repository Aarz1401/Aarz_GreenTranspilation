#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <unordered_set>

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