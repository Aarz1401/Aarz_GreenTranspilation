#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <string>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <limits>

using namespace std;

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        vector<array<int, 26>> sticker_counts;
        sticker_counts.reserve(stickers.size());
        for (const auto& s : stickers) {
            array<int, 26> cnt{};
            cnt.fill(0);
            for (char c : s) {
                if (c >= 'a' && c <= 'z') {
                    cnt[c - 'a']++;
                }
            }
            sticker_counts.push_back(cnt);
        }
        unordered_map<string, int> dp;
        dp[""] = 0;
        return helper(sticker_counts, target, dp);
    }

private:
    int helper(const vector<array<int, 26>>& sticker_counts, const string& target, unordered_map<string, int>& dp) {
        auto it = dp.find(target);
        if (it != dp.end()) return it->second;

        array<int, 26> target_count{};
        target_count.fill(0);
        for (char c : target) target_count[c - 'a']++;

        int result = numeric_limits<int>::max() / 2;
        for (const auto& sc : sticker_counts) {
            if (!target.empty() && sc[target[0] - 'a'] == 0) continue;
            string new_target;
            new_target.reserve(target.size());
            for (int k = 0; k < 26; ++k) {
                int remaining = target_count[k] - sc[k];
                if (remaining > 0) new_target.append(remaining, static_cast<char>('a' + k));
            }
            if (new_target.size() != target.size()) {
                int num = helper(sticker_counts, new_target, dp);
                if (num != -1) {
                    result = min(result, 1 + num);
                }
            }
        }
        dp[target] = (result >= numeric_limits<int>::max() / 2) ? -1 : result;
        return dp[target];
    }
};

struct TestCase {
    vector<string> stickers;
    string target;
};

int main() {
    vector<TestCase> tests;
    tests.reserve(10);
    tests.push_back({{"with","example","science"}, "thehat"});
    tests.push_back({{"notice","possible"}, "basicbasic"});
    tests.push_back({{"these","guess","about","garden","him"}, "atomher"});
    tests.push_back({{"travel","broadcast","player","game"}, "goal"});
    tests.push_back({{"aaaa","bbbb","cc","dd"}, "abcd"});
    tests.push_back({{"ab","bc","cd"}, "abcd"});
    tests.push_back({{"ab","ab","ab"}, "aabb"});
    tests.push_back({{"hello","world","leetcode"}, "hold"});
    tests.push_back({{"abc","abd","cde","def"}, "feed"});
    tests.push_back({{"letter","collection","stickers","random","words","for","testing"}, "score"});

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            int res = sol.minStickers(const_cast<vector<string>&>(tc.stickers), tc.target);
            DoNotOptimize(res);
            //checksum += res;
        }
        //sink = checksum;
    }

    return 0;
}