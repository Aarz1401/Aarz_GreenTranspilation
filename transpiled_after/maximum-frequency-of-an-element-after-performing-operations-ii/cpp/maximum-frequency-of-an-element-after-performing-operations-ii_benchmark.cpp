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
    // Define 10 diverse test inputs
    std::vector<TestCase> tests;

    // 1) Empty array
    tests.push_back({{}, 5, 3});

    // 2) Single element
    tests.push_back({{42}, 0, 0});

    // 3) All equal elements
    tests.push_back({{5, 5, 5, 5, 5}, 0, 10});

    // 4) Incremental sequence
    tests.push_back({{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 2, 3});

    // 5) Mixed negatives and positives
    tests.push_back({{-15, -10, -5, 0, 5, 10, 15}, 5, 4});

    // 6) Large k allows wide window
    tests.push_back({{1, 100, 200, 300, 400}, 1000, 2});

    // 7) k = 0 with duplicates
    tests.push_back({{1, 1, 2, 2, 3, 3, 3, 4}, 0, 2});

    // 8) Arithmetic progression, small k, large ops
    tests.push_back({{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, 1, 100});

    // 9) Near INT_MAX values to test long long arithmetic pathways
    tests.push_back({{INT_MAX - 100, INT_MAX - 3, INT_MAX - 2, INT_MAX - 1, INT_MAX}, 2, 3});

    // 10) Larger patterned array to exercise sliding windows and counts
    std::vector<int> v10;
    for (int j = 0; j < 100; ++j) {
        v10.push_back(((j * 37) % 100) - 50); // values in [-50, 49]
    }
    tests.push_back({v10, 10, 20});
    
    const int iterations = 1000;

    Solution sol;

    long long totalResult = 0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            int res = sol.maxFrequency(tc.nums, tc.k, tc.ops);
            totalResult += res;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Aggregate result: " << totalResult << "\n";
    std::cout << "Elapsed time (microseconds): " << micros << "\n";

    return 0;
}