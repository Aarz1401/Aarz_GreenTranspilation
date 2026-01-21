#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    int numPermsDISequence(std::string S) {
        const int MOD = 1000000007;
        int n = S.size();
        std::vector<int> dp(n + 1, 1);
        for (char c : S) {
            if (c == 'I') {
                dp.pop_back();
                for (int i = 1; i < static_cast<int>(dp.size()); ++i) {
                    dp[i] += dp[i - 1];
                    if (dp[i] >= MOD) dp[i] -= MOD;
                }
            } else {
                std::vector<int> newdp(dp.begin() + 1, dp.end());
                dp.swap(newdp);
                for (int i = static_cast<int>(dp.size()) - 2; i >= 0; --i) {
                    dp[i] += dp[i + 1];
                    if (dp[i] >= MOD) dp[i] -= MOD;
                }
            }
        }
        return dp[0] % MOD;
    }
};

volatile int sink = 0;

int main() {
    std::vector<std::string> tests = {
        "I",
        "D",
        "ID",
        "DI",
        "IID",
        "DDI",
        "IDIDID",
        "DDDDIIII",
        "IIDDDIII",
        "IDDIIDIDID"
    };

    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.numPermsDISequence(s);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}