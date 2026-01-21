#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <chrono>
#include <random>
#include <cstdint>
#include <climits>
#include <vector>
#include <deque>

#include <vector>
#include <deque>

using std::vector;
using std::deque;

class Solution {
public:
    // Time:  O(n)
    // Space: O(k)
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> result;
        if (k <= 0 || nums.empty()) return result;
        deque<int> dq;
        result.reserve(nums.size() >= static_cast<size_t>(k) ? nums.size() - k + 1 : 0);
        for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
            if (!dq.empty() && i - dq.front() == k) {
                dq.pop_front();
            }
            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        return result;
    }
};

int main() {
    // Generate 10 diverse test inputs
    std::vector<int> t1 = {1, 2, 3, 4, 5};
    int k1 = 3;

    std::vector<int> t2 = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int k2 = 4;

    std::vector<int> t3 = {7, 7, 7, 7, 7, 7, 7, 7};
    int k3 = 5;

    std::vector<int> t4 = {1, 100, 2, 99, 3, 98, 4, 97, 5, 96, 6, 95};
    int k4 = 3;

    std::vector<int> t5 = {INT_MIN, -1, INT_MAX, 0, INT_MIN + 1, INT_MAX - 1};
    int k5 = 2;

    // Random but deterministic inputs
    std::mt19937 rng(123456u);
    std::uniform_int_distribution<int> dist_small(-1000, 1000);
    std::uniform_int_distribution<int> dist_large(-1000000, 1000000);

    std::vector<int> t6(10);
    for (auto& v : t6) v = dist_small(rng);
    int k6 = 1;

    std::vector<int> t7(20);
    for (int i = 0; i < 20; ++i) t7[i] = i - 10; // includes negatives and positives
    int k7 = 20;

    std::vector<int> t8 = {3, 1, 4, 1, 5};
    int k8 = 10; // k > n

    std::vector<int> t9; // empty
    int k9 = 3;

    std::vector<int> t10(5000);
    for (auto& v : t10) v = dist_large(rng);
    int k10 = 128;

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        auto r1 = sol.maxSlidingWindow(t1, k1);
        for (int v : r1) checksum += static_cast<uint64_t>(v);

        auto r2 = sol.maxSlidingWindow(t2, k2);
        for (int v : r2) checksum += static_cast<uint64_t>(v);

        auto r3 = sol.maxSlidingWindow(t3, k3);
        for (int v : r3) checksum += static_cast<uint64_t>(v);

        auto r4 = sol.maxSlidingWindow(t4, k4);
        for (int v : r4) checksum += static_cast<uint64_t>(v);

        auto r5 = sol.maxSlidingWindow(t5, k5);
        for (int v : r5) checksum += static_cast<uint64_t>(v);

        auto r6 = sol.maxSlidingWindow(t6, k6);
        for (int v : r6) checksum += static_cast<uint64_t>(v);

        auto r7 = sol.maxSlidingWindow(t7, k7);
        for (int v : r7) checksum += static_cast<uint64_t>(v);

        auto r8 = sol.maxSlidingWindow(t8, k8);
        for (int v : r8) checksum += static_cast<uint64_t>(v);

        auto r9 = sol.maxSlidingWindow(t9, k9);
        for (int v : r9) checksum += static_cast<uint64_t>(v);

        auto r10 = sol.maxSlidingWindow(t10, k10);
        for (int v : r10) checksum += static_cast<uint64_t>(v);
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}