#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cstddef>

class Solution {
public:
    int removeBoxes(std::vector<int>& boxes) {
        int n = static_cast<int>(boxes.size());
        if (n == 0) return 0;

        std::vector<int> dp(n * n * n, 0);
        auto idx = [n](int l, int r, int k) -> size_t {
            return (static_cast<size_t>(l) * n + r) * n + k;
        };

        std::function<int(int,int,int)> dfs = [&](int l, int r, int k) -> int {
            if (l > r) return 0;
            size_t id = idx(l, r, k);
            if (dp[id] != 0) return dp[id];

            int ll = l, kk = k;
            while (l < r && boxes[l + 1] == boxes[l]) {
                ++l;
                ++k;
            }

            int result = dfs(l + 1, r, 0) + (k + 1) * (k + 1);
            for (int i = l + 1; i <= r; ++i) {
                if (boxes[i] == boxes[l]) {
                    result = std::max(result, dfs(l + 1, i - 1, 0) + dfs(i, r, k + 1));
                }
            }

            dp[idx(ll, r, kk)] = result;
            return result;
        };

        return dfs(0, n - 1, 0);
    }
};