#include <iostream>
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

int main() {
    std::vector<std::vector<int>> tests = {
        {1, 2, 0},
        {3, 4, -1, 1},
        {7, 8, 9, 11, 12},
        {1, 1},
        {2},
        {1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6},
        {1, 1, 0, -1, -2, 2, 2, 3, 4},
        {1},
        {10, 1, 2, 3, 4, 5, 6, 7, 8, 9}
    };

    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (const auto& t : tests) {
            std::vector<int> v = t;
            checksum += sol.firstMissingPositive(v);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}