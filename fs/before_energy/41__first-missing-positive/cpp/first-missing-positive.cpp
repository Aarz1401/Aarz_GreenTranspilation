#include <vector>
#include <algorithm>

class Solution {
public:
    // Time:  O(n)
    // Space: O(1)
    int firstMissingPositive(std::vector<int>& A) {
        int n = static_cast<int>(A.size());
        int i = 0;
        while (i < n) {
            if (A[i] > 0 && A[i] - 1 < n && A[i] != A[A[i] - 1]) {
                std::swap(A[i], A[A[i] - 1]);
            } else {
                ++i;
            }
        }

        for (int i = 0; i < n; ++i) {
            if (A[i] != i + 1) {
                return i + 1;
            }
        }
        return n + 1;
    }
};