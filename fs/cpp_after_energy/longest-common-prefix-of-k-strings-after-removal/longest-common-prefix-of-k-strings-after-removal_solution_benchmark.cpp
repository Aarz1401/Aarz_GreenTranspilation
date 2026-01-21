#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <numeric>
#include <chrono>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        int n = words.size();
        vector<int> idxs(n);
        iota(idxs.begin(), idxs.end(), 0);
        sort(idxs.begin(), idxs.end(), [&](int a, int b) {
            return words[a] < words[b];
        });

        auto lcp_for_k = [&](int kk) -> vector<int> {
            vector<int> lcp(n, 0);
            int upto = n - (kk - 1);
            if (upto < 0) upto = 0;
            for (int i = 0; i < upto; ++i) {
                const string& left = words[idxs[i]];
                const string& right = words[idxs[i + kk - 1]];
                int l = static_cast<int>(min(left.size(), right.size()));
                int j = 0;
                while (j < l && left[j] == right[j]) {
                    ++j;
                }
                lcp[i] = j;
            }
            return lcp;
        };

        vector<int> lcp = lcp_for_k(k);

        vector<int> prefix(n, 0);
        if (n > 0) {
            prefix[0] = lcp[0];
            for (int i = 0; i + 1 < n; ++i) {
                prefix[i + 1] = max(prefix[i], lcp[i + 1]);
            }
        }

        vector<int> suffix(n, 0);
        if (n > 0) {
            suffix[n - 1] = lcp[n - 1];
            for (int i = n - 2; i >= 0; --i) {
                suffix[i] = max(suffix[i + 1], lcp[i]);
            }
        }

        vector<int> res(n, 0);
        vector<int> lcp_k1 = lcp_for_k(k + 1);
        int mx = 0;
        if (!lcp_k1.empty()) {
            mx = *max_element(lcp_k1.begin(), lcp_k1.end());
        }

        for (int i = 0; i < n; ++i) {
            int origIdx = idxs[i];
            int mx1 = (i - k >= 0) ? prefix[i - k] : 0;
            int mx2 = (i + 1 < n) ? suffix[i + 1] : 0;
            res[origIdx] = max({mx, mx1, mx2});
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Prepare 10 diverse test inputs
    vector<pair<vector<string>, int>> tests;
    tests.reserve(10);

    // 1. Empty list
    tests.push_back({{}, 1});

    // 2. Single word
    tests.push_back({{"hello"}, 1});

    // 3. All same words
    tests.push_back({{"aaa", "aaa", "aaa", "aaa"}, 2});

    // 4. No common prefixes
    tests.push_back({{"dog", "cat", "bird", "fish"}, 2});

    // 5. Common prefixes among many
    tests.push_back({{"interview", "interval", "internal", "internet"}, 3});

    // 6. k equals n
    tests.push_back({{"alpha", "alpine", "altar", "altruist", "algebra"}, 5});

    // 7. k greater than n
    tests.push_back({{"abc", "abd"}, 3});

    // 8. Chain of prefixes
    tests.push_back({{"a", "ab", "abc", "abcd", "abcde"}, 4});

    // 9. Case sensitivity and ordering
    tests.push_back({{"Apple", "application", "app", "App", "apply"}, 2});

    // 10. Long strings
    {
        string x1000(1000, 'x');
        string a = x1000 + "a";
        string b = x1000 + "b";
        string c = string(999, 'x') + 'y';
        string d(1000, 'z');
        tests.push_back({{a, b, c, d}, 2});
    }

    Solution sol;
    long long checksum = 0;

    using hrc = std::chrono::high_resolution_clock;
    auto start = hrc::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            vector<int> res = sol.longestCommonPrefix(t.first, t.second);
            for (int v : res) checksum += v;
            checksum += static_cast<long long>(t.first.size() * 131 + t.second);
        }
    }

    auto end = hrc::now();
    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << duration_ns << "\n";

    return 0;
}