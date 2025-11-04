#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <array>
#include <algorithm>
#include <limits>
#include <chrono>
#include <utility>

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<vector<string>, string>> tests;
    tests.reserve(10);
    tests.emplace_back(vector<string>{"with","example","science"}, "thehat");
    tests.emplace_back(vector<string>{"notice","possible"}, "basicbasic");
    tests.emplace_back(vector<string>{"these","guess","about","garden","him"}, "atomher");
    tests.emplace_back(vector<string>{"a","b","c"}, "abccba");
    tests.emplace_back(vector<string>{"ab","bc","ca"}, "abccab");
    tests.emplace_back(vector<string>{"aaaa","b","c","d"}, "aaaaa");
    tests.emplace_back(vector<string>{"abc","abd","acd","bcd"}, "abcd");
    tests.emplace_back(vector<string>{"with","out","input","stickers"}, "withoutstickers");
    tests.emplace_back(vector<string>{"the","quick","brown","fox","jumps","over","lazy","dog"}, "thequickbrownfox");
    tests.emplace_back(vector<string>{"abc","def"}, "");

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            auto& stickers = tests[i].first;
            auto& target = tests[i].second;
            int res = sol.minStickers(stickers, target);
            checksum += static_cast<long long>(res) * static_cast<long long>(i + 1);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}