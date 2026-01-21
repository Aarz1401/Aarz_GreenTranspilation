#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <string>

using namespace std;

class Solution {
public:
    int countWinningSequences(string s) {
        const int MOD = 1000000007;
        if (s.empty()) return 0;

        array<int, 128> lookup;
        lookup.fill(-1);
        lookup['F'] = 0;
        lookup['W'] = 1;
        lookup['E'] = 2;

        vector<unordered_map<int, int>> dp(3);
        for (int i = 0; i < (int)s.size(); ++i) {
            vector<unordered_map<int, int>> new_dp(3);
            int x = lookup[(unsigned char)s[i]];
            for (int j = 0; j < 3; ++j) {
                int m = ((j - x + 1) % 3 + 3) % 3;
                int diff = m - 1;
                if (i == 0) {
                    new_dp[j][diff] = 1;
                    continue;
                }
                for (int k = 0; k < 3; ++k) {
                    if (k == j) continue;
                    for (const auto& p : dp[k]) {
                        int v = p.first;
                        int cnt = p.second;
                        long long add = new_dp[j][v + diff];
                        add += cnt;
                        if (add >= MOD) add -= MOD;
                        new_dp[j][v + diff] = (int)add;
                    }
                }
            }
            dp.swap(new_dp);
        }

        long long ans = 0;
        for (int j = 0; j < 3; ++j) {
            for (const auto& p : dp[j]) {
                int v = p.first;
                int cnt = p.second;
                if (v >= 1) {
                    ans += cnt;
                    if (ans >= MOD) ans -= MOD;
                }
            }
        }
        return (int)(ans % MOD);
    }
};

int main() {
    vector<string> tests = {
        "F",
        "W",
        "E",
        "FW",
        "WEF",
        "FFWE",
        "FWEFWE",
        "EEEEWWWWFFFF",
        "FEWEWFEWFWEE",
        "FWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWE"
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.countWinningSequences(s);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}