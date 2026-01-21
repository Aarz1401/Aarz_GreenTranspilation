#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <functional>
#include <algorithm>
#include <cstddef>
#include <chrono>

class Solution {
public:
    int removeBoxes(std::vector<int>& boxes) {
        int n = static_cast<int>(boxes.size());
        if (n == 0) return 0;

        std::vector<int> dp(n * n * n, 0);
        auto idx = [n](int l, int r, int k) -> size_t {
            return (static_cast<size_t>(l) * n + r) * n + k;
        };

        std::function<int(int,int,int)> dfs = [&](int l, int r, int k) -> int {
            if (l > r) return 0;
            size_t id = idx(l, r, k);
            if (dp[id] != 0) return dp[id];

            int ll = l, kk = k;
            while (l < r && boxes[l + 1] == boxes[l]) {
                ++l;
                ++k;
            }

            int result = dfs(l + 1, r, 0) + (k + 1) * (k + 1);
            for (int i = l + 1; i <= r; ++i) {
                if (boxes[i] == boxes[l]) {
                    result = std::max(result, dfs(l + 1, i - 1, 0) + dfs(i, r, k + 1));
                }
            }

            dp[idx(ll, r, kk)] = result;
            return result;
        };

        return dfs(0, n - 1, 0);
    }
};

int main() {
    // Define 10 diverse test inputs
    std::vector<std::vector<int>> tests;
    tests.push_back({}); // empty
    tests.push_back({7}); // single element
    tests.push_back({1, 2}); // two different
    tests.push_back({1, 1, 1, 1, 1}); // all same
    tests.push_back({1, 2, 3, 4, 5, 6}); // all distinct, increasing
    tests.push_back({1, 1, 2, 2, 3, 3, 4, 4}); // pairs
    tests.push_back({1, 2, 2, 2, 1}); // merge same ends via middle block
    tests.push_back({3, 3, 2, 1, 2, 3, 3}); // symmetric groups with merges
    tests.push_back({1, 2, 1, 2, 1, 2, 1}); // alternating
    tests.push_back({1, 1, 1, 2, 2, 3, 3, 3, 2, 2, 1, 1}); // larger mixed groups

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            int result = sol.removeBoxes(t);
            checksum += static_cast<uint64_t>(result);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}