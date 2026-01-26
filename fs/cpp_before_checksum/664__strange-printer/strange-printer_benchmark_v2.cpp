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
        "a",
        "aaaaaaa",
        "ab",
        "aba",
        "abcabcabc",
        "aaabbbccc",
        "abaabbba",
        "abcdedcba",
        "bacabacaba",
        "thequickbrownfox"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.strangePrinter(s);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}