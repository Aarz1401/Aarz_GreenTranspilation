#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <limits>
#include <chrono>
#include <random>
#include <cstdint>

class Solution {
public:
    std::vector<int> maxSumOfThreeSubarrays(std::vector<int>& nums, int k) {
        int n = nums.size();
        std::vector<long long> accu(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            accu[i + 1] = accu[i] + nums[i];
        }

        std::vector<int> left_pos(n, 0);
        long long total = accu[k] - accu[0];
        for (int i = k; i < n; ++i) {
            long long cur = accu[i + 1] - accu[i + 1 - k];
            if (cur > total) {
                left_pos[i] = i + 1 - k;
                total = cur;
            } else {
                left_pos[i] = left_pos[i - 1];
            }
        }

        std::vector<int> right_pos(n, n - k);
        total = accu[n] - accu[n - k];
        for (int i = n - k - 1; i >= 0; --i) {
            long long cur = accu[i + k] - accu[i];
            if (cur > total) {
                right_pos[i] = i;
                total = cur;
            } else {
                right_pos[i] = right_pos[i + 1];
            }
        }

        std::vector<int> result;
        long long max_sum = 0;
        for (int i = k; i <= n - 2 * k; ++i) {
            int left = left_pos[i - 1];
            int right = right_pos[i + k];
            long long cur = (accu[i + k] - accu[i]) +
                            (accu[left + k] - accu[left]) +
                            (accu[right + k] - accu[right]);
            if (cur > max_sum) {
                max_sum = cur;
                result = {left, i, right};
            }
        }

        return result;
    }
};

struct TestCase {
    std::vector<int> nums;
    int k;
};

int main() {
    // Define 10 diverse test inputs
    std::vector<TestCase> tests;
    tests.reserve(10);

    // 1) Small k=1 case
    tests.push_back(TestCase{{1,2,1,2,6,7,5,1,2}, 1});

    // 2) Classic sample-like case
    tests.push_back(TestCase{{1,2,1,2,6,7,5,1}, 2});

    // 3) All equal numbers
    tests.push_back(TestCase{std::vector<int>(12, 5), 2});

    // 4) Increasing sequence
    {
        std::vector<int> v(30);
        for (int i = 0; i < 30; ++i) v[i] = i + 1;
        tests.push_back(TestCase{std::move(v), 3});
    }

    // 5) Decreasing sequence
    {
        std::vector<int> v(30);
        for (int i = 0; i < 30; ++i) v[i] = 30 - i;
        tests.push_back(TestCase{std::move(v), 3});
    }

    // 6) Mostly zeros with spikes
    {
        std::vector<int> v(27, 0);
        for (int i = 3; i < 6; ++i) v[i] = 10;
        for (int i = 10; i < 13; ++i) v[i] = 20;
        for (int i = 20; i < 23; ++i) v[i] = 30;
        tests.push_back(TestCase{std::move(v), 3});
    }

    // 7) Large random array
    {
        std::mt19937 rng(12345);
        std::uniform_int_distribution<int> dist(0, 100);
        std::vector<int> v(3000);
        for (int& x : v) x = dist(rng);
        tests.push_back(TestCase{std::move(v), 10});
    }

    // 8) Minimal n = 3k case with alternating values
    {
        std::vector<int> v = {5,1,5,1,5,1,5,1,5,1,5,1,5,1,5}; // n = 15
        tests.push_back(TestCase{std::move(v), 5});
    }

    // 9) Large k=1 patterned values
    {
        std::vector<int> v(1000);
        for (int i = 0; i < 1000; ++i) v[i] = (i * 37 + 13) % 101;
        tests.push_back(TestCase{std::move(v), 1});
    }

    // 10) k near n/3 with random values
    {
        std::mt19937 rng(2021);
        std::uniform_int_distribution<int> dist(0, 50);
        std::vector<int> v(60);
        for (int& x : v) x = dist(rng);
        tests.push_back(TestCase{std::move(v), 20});
    }

    Solution sol;
    volatile unsigned long long checksum = 0; // volatile to prevent optimization

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::microseconds;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            // We need a non-const reference; copy a reference to the stored vector
            // The solution does not modify the vector.
            std::vector<int> &numsRef = const_cast<std::vector<int>&>(tc.nums);
            auto res = sol.maxSumOfThreeSubarrays(numsRef, tc.k);
            if (res.size() == 3) {
                checksum += static_cast<unsigned long long>(res[0]) * 1000003ULL;
                checksum += static_cast<unsigned long long>(res[1]) * 10007ULL;
                checksum += static_cast<unsigned long long>(res[2]) * 101ULL;
            } else {
                checksum += 1ULL; // fallback in case of unexpected empty result
            }
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}