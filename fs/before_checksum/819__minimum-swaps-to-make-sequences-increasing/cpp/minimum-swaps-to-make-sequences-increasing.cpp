#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <limits>

class Solution {
public:
    int minSwap(std::vector<int>& A, std::vector<int>& B) {
        // Time:  O(n)
        // Space: O(1)
        int n = static_cast<int>(A.size());
        if (n <= 1) return 0;

        const int INF = std::numeric_limits<int>::max() / 4;
        std::array<int, 2> dp_no_swap = {0, 0};
        std::array<int, 2> dp_swap = {1, 1};

        for (int i = 1; i < n; ++i) {
            int cur = i & 1;
            int prev = (i - 1) & 1;
            dp_no_swap[cur] = INF;
            dp_swap[cur] = INF;

            if (A[i - 1] < A[i] && B[i - 1] < B[i]) {
                dp_no_swap[cur] = std::min(dp_no_swap[cur], dp_no_swap[prev]);
                dp_swap[cur] = std::min(dp_swap[cur], dp_swap[prev] + 1);
            }
            if (A[i - 1] < B[i] && B[i - 1] < A[i]) {
                dp_no_swap[cur] = std::min(dp_no_swap[cur], dp_swap[prev]);
                dp_swap[cur] = std::min(dp_swap[cur], dp_no_swap[prev] + 1);
            }
        }
        return std::min(dp_no_swap[(n - 1) & 1], dp_swap[(n - 1) & 1]);
    }
};