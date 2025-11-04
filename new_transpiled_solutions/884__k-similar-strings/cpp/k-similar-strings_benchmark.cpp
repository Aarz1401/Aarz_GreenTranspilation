#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <chrono>

// Time:  O(n * n!/(c_a!*...*c_z!), n is the length of A, B,
//                                  c_a...c_z is the count of each alphabet,
//                                  n = sum(c_a...c_z)
// Space: O(n * n!/(c_a!*...*c_z!)

class Solution {
public:
    int kSimilarity(std::string A, std::string B) {
        auto neighbors = [&](const std::string& s) -> std::vector<std::string> {
            int i = 0, n = static_cast<int>(s.size());
            for (; i < n; ++i) {
                if (s[i] != B[i]) break;
            }
            std::vector<std::string> res;
            if (i == n) return res;
            std::string t = s;
            for (int j = i + 1; j < n; ++j) {
                if (t[j] == B[i]) {
                    std::swap(t[i], t[j]);
                    res.emplace_back(t);
                    std::swap(t[j], t[i]);
                }
            }
            return res;
        };

        std::queue<std::string> q;
        q.push(A);
        std::unordered_set<std::string> lookup;
        int result = 0;

        while (!q.empty()) {
            int sz = static_cast<int>(q.size());
            for (int _ = 0; _ < sz; ++_) {
                std::string s = q.front(); q.pop();
                if (s == B) {
                    return result;
                }
                for (const auto& t : neighbors(s)) {
                    if (!lookup.count(t)) {
                        lookup.insert(t);
                        q.push(t);
                    }
                }
            }
            ++result;
        }
        return result;
    }
};

int main() {
    using namespace std;
    using namespace std::chrono;

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs (pairs of anagram strings)
    vector<pair<string, string>> tests = {
        {"ab", "ab"},          // identical strings
        {"ab", "ba"},          // single swap needed
        {"aabc", "abca"},      // duplicates with small length
        {"abc", "bca"},        // rotation-like
        {"aabb", "bbaa"},      // duplicates reversed
        {"abac", "baca"},      // mixed duplicates
        {"abcdef", "fabcde"},  // longer permutation
        {"aabbcc", "ccbbaa"},  // more duplicates
        {"a", "a"},            // minimal length
        {"abcde", "abced"}     // near-sorted with a swap near the end
    };

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& p : tests) {
            checksum += sol.kSimilarity(p.first, p.second);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_ms = duration_cast<duration<double, std::milli>>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}