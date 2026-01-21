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
#include <deque>
#include <chrono>

using namespace std;

class Solution {
public:
    string generateString(string str1, string str2) {
        auto z_function = [](const string& s) {
            vector<int> z(s.size(), 0);
            int l = 0, r = 0;
            for (int i = 1; i < (int)s.size(); ++i) {
                if (i <= r) {
                    z[i] = min(r - i + 1, z[i - l]);
                }
                while (i + z[i] < (int)s.size() && s[z[i]] == s[i + z[i]]) {
                    ++z[i];
                }
                if (i + z[i] - 1 > r) {
                    l = i;
                    r = i + z[i] - 1;
                }
            }
            return z;
        };

        int n = str1.size(), m = str2.size();
        string candidate(n + m - 1, '*');
        vector<int> z = z_function(str2);
        int prev = -m;
        for (int i = 0; i < n; ++i) {
            char x = str1[i];
            if (x != 'T') {
                continue;
            }
            int diff = i - prev;
            if (diff < m) {
                if (z[diff] == m - diff) {
                    // candidate[prev+m : i+m] = str2[m-diff :]
                    int startCand = prev + m;
                    int startStr2 = m - diff;
                    for (int k = 0; k < diff; ++k) {
                        candidate[startCand + k] = str2[startStr2 + k];
                    }
                } else {
                    return "";
                }
            } else {
                // candidate[i : i+m] = str2
                for (int k = 0; k < m; ++k) {
                    candidate[i + k] = str2[k];
                }
            }
            prev = i;
        }
        string result = str2 + "#" + candidate;
        vector<int> idxs;
        for (int i = m + 1; i < (int)result.size(); ++i) {
            if (result[i] == '*') {
                result[i] = 'a';
                idxs.push_back(i);
            }
        }
        vector<int> z_all = z_function(result);
        deque<int> dq;
        int i = m + 1;
        int j = 0;
        while (i - (m + 1) < n) {
            while (!dq.empty() && dq.front() < i) {
                dq.pop_front();
            }
            while (j < (int)idxs.size() && idxs[j] <= i + (m - 1)) {
                dq.push_back(idxs[j]);
                ++j;
            }
            if (str1[i - (m + 1)] == 'F' && z_all[i] == m) {
                if (dq.empty()) {
                    return "";
                }
                result[dq.back()] = 'b';
                i += m;
            } else {
                ++i;
            }
        }
        return result.substr(m + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<pair<string, string>> tests = {
        {"FFFFF", "ab"},                 // Mostly F, simple pattern
        {"TTTT", "aba"},                 // Overlapping T's that likely conflict (expected failure)
        {"TTTFFFF", "aaa"},              // Overlapping T's with compatible pattern
        {"FFTFFTF", "aba"},              // Mixed constraints
        {"", "abc"},                     // Empty str1
        {"T", "b"},                      // Single T and single-letter str2
        {"FTFTFTFTFT", "b"},             // Alternating constraints with m=1
        {"FFFFFFFF", "a"},               // All F with m=1
        {"TT", "ababa"},                 // Conflicting overlaps (expected failure)
        {"TFFTTFTFTFTTFTFFFTFTTTFTFF", "aababa"} // Larger mixed case
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            string res = sol.generateString(tc.first, tc.second);
            // Update checksum to avoid optimization
            // Simple mixing of size and few characters
            checksum ^= static_cast<unsigned long long>(res.size()) + 0x9e3779b97f4a7c15ULL + (checksum << 6) + (checksum >> 2);
            if (!res.empty()) {
                checksum += static_cast<unsigned long long>(static_cast<unsigned char>(res[0]));
                checksum += static_cast<unsigned long long>(static_cast<unsigned char>(res.back()));
            } else {
                checksum += 1ULL; // distinguish empty results
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}