#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <limits>
#include <chrono>
#include <iomanip>
#include <utility>
#include <climits>

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
    vector<pair<vector<int>, vector<int>>> tests;
    tests.reserve(10);

    tests.emplace_back(vector<int>{}, vector<int>{1});
    tests.emplace_back(vector<int>{}, vector<int>{1, 2, 3, 4});
    tests.emplace_back(vector<int>{1, 3}, vector<int>{2});
    tests.emplace_back(vector<int>{1, 2}, vector<int>{3, 4});
    tests.emplace_back(vector<int>{-5, -3, -1}, vector<int>{-2, 0, 2});
    tests.emplace_back(vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1});
    tests.emplace_back(vector<int>{INT_MIN, -1, 0, 1, INT_MAX}, vector<int>{-2, 2});
    {
        vector<int> evens;
        vector<int> odds;
        evens.reserve(100);
        odds.reserve(100);
        for (int i = 0; i < 100; ++i) {
            evens.push_back(i * 2);
            odds.push_back(i * 2 + 1);
        }
        tests.emplace_back(move(evens), move(odds));
    }
    tests.emplace_back(vector<int>{5}, vector<int>{1, 2, 3, 4, 6, 7, 8, 9, 10});
    tests.emplace_back(vector<int>{-10, -10, -5, 0, 0, 0, 5}, vector<int>{-7, -3, -3, 2, 4, 4, 20});

    Solution s;

    auto start = chrono::high_resolution_clock::now();
    double checksum = 0.0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += s.findMedianSortedArrays(tests[i].first, tests[i].second);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> elapsed = end - start;

    cout << fixed << setprecision(6);
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";
    return 0;
}