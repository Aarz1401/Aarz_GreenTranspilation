#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <limits>
using namespace std;

// Time:  O(log(min(m, n)))
// Space: O(1)
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        // binary_search returns the smallest index i in [left, right] such that check(i) is true
        auto binary_search = [&](int left, int right, const function<bool(int)>& check) -> int {
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (check(mid)) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            return left;
        };

        auto getKth = [&](const vector<int>& A1, const vector<int>& B1, int k) -> int {
            const vector<int>* A = &A1;
            const vector<int>* B = &B1;
            int m = static_cast<int>(A->size());
            int n = static_cast<int>(B->size());
            if (m > n) {
                swap(A, B);
                swap(m, n);
            }
            int left = max(k - n, 0);
            int right = min(m, k) - 1;
            auto check = [&](int i) -> bool {
                int j = k - 1 - i;
                return (*A)[i] >= (*B)[j];
            };
            int i = binary_search(left, right, check);
            long long leftA = (i - 1 >= 0) ? static_cast<long long>((*A)[i - 1]) : numeric_limits<long long>::min();
            int j = k - 1 - i;
            long long leftB = (j >= 0) ? static_cast<long long>((*B)[j]) : numeric_limits<long long>::min();
            long long ans = max(leftA, leftB);
            return static_cast<int>(ans);
        };

        int len1 = static_cast<int>(nums1.size());
        int len2 = static_cast<int>(nums2.size());
        int total = len1 + len2;
        if (total % 2 == 1) {
            return static_cast<double>(getKth(nums1, nums2, total / 2 + 1));
        } else {
            int a = getKth(nums1, nums2, total / 2);
            int b = getKth(nums1, nums2, total / 2 + 1);
            return (static_cast<double>(a) + static_cast<double>(b)) * 0.5;
        }
    }
};

// Time:  O(log(max(m, n)) * log(max_val - min_val))
// Space: O(1)
// Generic solution.

int main() {
    vector<vector<vector<int>>> tests = {
        { {1, 3}, {2} },
        { {1, 2}, {3, 4} },
        { {0, 0, 0, 0}, {1, 2, 3} },
        { {-5, -3, -1}, {-2, 0, 2, 4} },
        { {1, 1, 1, 1, 1}, {1, 1, 2, 2, 2} },
        { {-2147483647, -1000000000, 0, 1000000000, 2147483647}, {-999999999, -1, 1, 999999999} },
        { {1, 3, 5, 7, 9, 11, 13, 15}, {2} },
        { {10}, {20} },
        { {100, 200, 300}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} },
        { {1}, {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int t = 0; t < static_cast<int>(tests.size()); ++t) {
            vector<int>& a = tests[t][0];
            vector<int>& b = tests[t][1];
            double res = sol.findMedianSortedArrays(a, b);
            checksum += static_cast<int>(res);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}