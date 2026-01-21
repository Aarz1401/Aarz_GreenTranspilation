#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <chrono>

class Solution {
public:
    int maxFrequency(std::vector<int>& nums, int k, int numOperations) {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        long long result = 0;
        int left = 0, right = -1;
        std::unordered_map<long long, int> cnt;

        for (int i = 0; i < n; ++i) {
            while (right + 1 < n && static_cast<long long>(nums[right + 1]) - nums[i] <= k) {
                cnt[nums[right + 1]] += 1;
                ++right;
            }
            while (static_cast<long long>(nums[i]) - nums[left] > k) {
                auto it = cnt.find(nums[left]);
                if (it != cnt.end()) {
                    if (--(it->second) == 0) {
                        cnt.erase(it);
                    }
                }
                ++left;
            }
            int total = right - left + 1;
            int c = cnt.count(nums[i]) ? cnt[nums[i]] : 0;
            result = std::max<long long>(result, c + std::min(numOperations, total - c));
        }

        left = 0;
        for (int r = 0; r < n; ++r) {
            while (static_cast<long long>(nums[left]) + k < static_cast<long long>(nums[r]) - k) {
                ++left;
            }
            result = std::max<long long>(result, std::min(numOperations, r - left + 1));
        }

        if (result > n) result = n;
        return static_cast<int>(result);
    }
};

struct TestCase {
    std::vector<int> nums;
    int k;
    int ops;
};

int main() {
    // Generate diverse test inputs
    std::vector<TestCase> tests;
    // 1. Empty array
    tests.push_back(TestCase{{}, 5, 3});
    // 2. Single element
    tests.push_back(TestCase{{10}, 0, 0});
    // 3. All equal
    tests.push_back(TestCase{{5, 5, 5, 5, 5}, 0, 0});
    // 4. Increasing with small k
    tests.push_back(TestCase{{1, 2, 4, 7, 7, 8, 12}, 2, 2});
    // 5. Negative and positive values
    tests.push_back(TestCase{{-10, -8, -7, -3, 0, 1, 2, 9}, 3, 3});
    // 6. Large k dominates distances
    tests.push_back(TestCase{{1, 100, 200, 300, 400, 500}, 1000, 2});
    // 7. Many duplicates with a small window
    tests.push_back(TestCase{{1, 1, 2, 2, 2, 3, 3, 4, 4, 4, 4}, 1, 3});
    // 8. Zero k with large operations
    tests.push_back(TestCase{{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 0, 100});
    // 9. Larger patterned array
    {
        std::vector<int> arr9;
        for (int i = 0; i < 120; ++i) {
            int v = (i * i * 31) % 2001 - 1000; // values in [-1000, 1000]
            arr9.push_back(v);
        }
        tests.push_back(TestCase{arr9, 10, 20});
    }
    // 10. Extreme integer values
    tests.push_back(TestCase{{INT_MIN, INT_MIN + 1, -1, 0, 1, INT_MAX - 1, INT_MAX}, 2, 3});

    Solution sol;
    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            std::vector<int> numsCopy = tc.nums; // ensure sort cost each iteration
            int res = sol.maxFrequency(numsCopy, tc.k, tc.ops);
            checksum += res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";

    return 0;
}