#include <vector>
#include <unordered_map>
#include <cstdint>

class Solution {
public:
    int numberOfArithmeticSlices(std::vector<int>& A) {
        // Time:  O(n^2)
        // Space: O(n * d)
        int n = static_cast<int>(A.size());
        long long result = 0;
        std::vector<std::unordered_map<long long, long long>> dp(n);
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                long long diff = static_cast<long long>(A[i]) - static_cast<long long>(A[j]);
                long long cnt = 0;
                auto it = dp[j].find(diff);
                if (it != dp[j].end()) {
                    cnt = it->second;
                }
                result += cnt;               // count subsequences extended to length >= 3
                dp[i][diff] += cnt + 1;      // +1 accounts for the pair (j, i)
            }
        }
        return static_cast<int>(result);
    }
};