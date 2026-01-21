#include <iostream>
#include <algorithm>
#include <cstdint>

// Time:  O(m * log(m * n))
// Space: O(1)

class Solution {
public:
    int findKthNumber(int m, int n, int k) {
        auto count = [&](long long target) -> long long {
            long long cnt = 0;
            for (int i = 1; i <= m; ++i) {
                cnt += std::min<long long>(target / i, n);
            }
            return cnt;
        };

        long long left = 1, right = 1LL * m * n;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            if (count(mid) >= k) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return static_cast<int>(left);
    }
};