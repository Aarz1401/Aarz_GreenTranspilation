#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

// Time:  O(n^3)
// Space: O(n^2)

class Solution {
public:
    int strangePrinter(string s) {
        int n = static_cast<int>(s.size());
        if (n == 0) return 0;

        vector<vector<int>> memo(n, vector<int>(n, 0));

        function<int(int, int)> dp = [&](int i, int j) -> int {
            if (i > j) return 0;
            int& res = memo[i][j];
            if (res != 0) return res;

            res = dp(i, j - 1) + 1;
            for (int k = i; k < j; ++k) {
                if (s[k] == s[j]) {
                    res = min(res, dp(i, k) + dp(k + 1, j - 1));
                }
            }
            return res;
        };

        return dp(0, n - 1);
    }
};

int main() {
    vector<string> tests = {
        "",                 // empty
        "a",                // single char
        "aaaaaa",           // all same
        "ababababa",        // alternating
        "abcde",            // all distinct
        "aaabbbccc",        // grouped repeats
        "aba",              // palindrome
        "abcbaabcba",       // repeated palindrome segments
        "bacbacbacb",       // repeating pattern
        "zzzyxyzzxxyyzz"    // mixed repeats
    };

    Solution sol;
    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            checksum += sol.strangePrinter(s);
        }
    }

    auto end = high_resolution_clock::now();
    double elapsed_ms = duration_cast<duration<double, std::milli>>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed ms: " << elapsed_ms << "\n";

    return 0;
}