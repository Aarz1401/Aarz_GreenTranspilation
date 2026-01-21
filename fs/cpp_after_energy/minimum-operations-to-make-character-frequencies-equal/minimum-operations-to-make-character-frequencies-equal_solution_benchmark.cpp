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
#include <chrono>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int makeStringGood(string s) {
        vector<int> cnt(26, 0);
        for (char x : s) {
            cnt[x - 'a'] += 1;
        }
        int n = static_cast<int>(s.size());
        int result = n;
        int minf = INT_MAX, maxf = 0;
        for (int c : cnt) {
            if (c > 0) {
                minf = min(minf, c);
                maxf = max(maxf, c);
            }
        }
        if (maxf == 0) {
            return 0;
        }
        for (int f = minf; f <= maxf; ++f) {
            int dp1 = 0, dp2 = 0;
            const int iterations = 1000;
            for (int iter = 0; iter < iterations; ++iter) {
                if (cnt[i] == 0) {
                    continue;
                }
                int new_dp1 = 0, new_dp2 = 0;
                if (cnt[i] >= f) {
                    new_dp1 = n;
                    new_dp2 = min(dp1, dp2) + (cnt[i] - f);
                } else {
                    int prev = (i - 1 >= 0) ? cnt[i - 1] : 0;
                    int free = (prev >= f) ? (prev - f) : prev;
                    new_dp1 = min(min(dp1, dp2) + (f - cnt[i]),
                                  dp2 + max((f - cnt[i]) - free, 0));
                    new_dp2 = min(dp1, dp2) + cnt[i];
                }
                dp1 = new_dp1;
                dp2 = new_dp2;
            }
            result = min(result, min(dp1, dp2));
        }
        return result;
    }
};

// Global variable to satisfy the use of 'i' in the original Solution without modification.
int i = 0;

int main() {
    // Prepare 10 diverse test inputs (strings as required by the solution)
    vector<string> tests;
    tests.push_back(""); // 1. empty
    tests.push_back("a"); // 2. single char
    tests.push_back("aaaaaaa"); // 3. uniform
    tests.push_back("abc"); // 4. small distinct
    tests.push_back("abababababababababababab"); // 5. alternating pattern
    tests.push_back("thequickbrownfoxjumpsoveralazydog"); // 6. pangram
    tests.push_back("mississippi"); // 7. repeated clusters
    {
        string t8;
        for (char c = 'a'; c <= 'z'; ++c) t8.push_back(c);
        tests.push_back(t8); // 8. full alphabet once
    }
    {
        string t9;
        t9.append(500, 'a');
        t9.append(500, 'b');
        tests.push_back(t9); // 9. large two-char block
    }
    {
        string t10;
        for (int k = 0; k < 100; ++k) t10 += "leetcode";
        tests.push_back(t10); // 10. repeated word
    }

    Solution sol;
    long long checksum = 0;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += sol.makeStringGood(s);
        }
    }

    auto end = high_resolution_clock::now();
    double elapsed_ms = duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}