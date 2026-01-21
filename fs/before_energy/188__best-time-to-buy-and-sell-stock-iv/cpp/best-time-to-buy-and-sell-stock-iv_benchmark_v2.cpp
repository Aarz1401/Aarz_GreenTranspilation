#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <limits>

class Solution {
public:
    int maxProfit(int k, std::vector<int>& prices) {
        // Time:  O(n) on average, using Median of Medians could achieve O(n) (Intro Select)
        // Space: O(n)

        // nth_element implementation with tri-partition and random pivot
        auto nth_element_custom = [&](std::vector<int>& nums, int n, auto compare) {
            auto tri_partition = [&](std::vector<int>& arr, int left, int right, int target, auto compare) -> std::pair<int, int> {
                int mid = left;
                while (mid <= right) {
                    if (arr[mid] == target) {
                        ++mid;
                    } else if (compare(arr[mid], target)) {
                        std::swap(arr[left], arr[mid]);
                        ++left;
                        ++mid;
                    } else {
                        std::swap(arr[mid], arr[right]);
                        --right;
                    }
                }
                return {left, right};
            };

            int left = 0, right = static_cast<int>(nums.size()) - 1;
            std::mt19937 gen(std::random_device{}());
            while (left <= right) {
                std::uniform_int_distribution<int> dist(left, right);
                int pivot_idx = dist(gen);
                auto bounds = tri_partition(nums, left, right, nums[pivot_idx], compare);
                if (bounds.first <= n && n <= bounds.second) {
                    return;
                } else if (n < bounds.first) {
                    right = bounds.first - 1;
                } else {  // bounds.second < n
                    left = bounds.second + 1;
                }
            }
        };

        std::vector<int> profits;
        std::vector<std::pair<int, int>> v_p_stk;  // mono stack, where v is increasing and p is strictly decreasing
        int v = -1, p = -1;
        const int n = static_cast<int>(prices.size());
        while (p + 1 < n) { // at most O(n) peaks, so v_p_stk and profits are both at most O(n) space
            bool found = false;
            for (v = p + 1; v < n - 1; ++v) {
                if (prices[v] < prices[v + 1]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                v = n - 1;
            }
            found = false;
            for (p = v; p < n - 1; ++p) {
                if (prices[p] > prices[p + 1]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                p = n - 1;
            }
            while (!v_p_stk.empty() && prices[v_p_stk.back().first] > prices[v]) {  // not overlapped
                auto last = v_p_stk.back(); v_p_stk.pop_back();
                profits.push_back(prices[last.second] - prices[last.first]);  // count [prices[last_v], prices[last_p]] interval
            }
            while (!v_p_stk.empty() && prices[v_p_stk.back().second] <= prices[p]) {  // overlapped
                // prices[last_v] <= prices[v] <= prices[last_p] <= prices[p],
                // treat overlapped as [prices[v], prices[last_p]], [prices[last_v], prices[p]] intervals due to invariant max profit
                auto last = v_p_stk.back(); v_p_stk.pop_back();
                profits.push_back(prices[last.second] - prices[v]);  // count [prices[v], prices[last_p]] interval
                v = last.first;
            }
            v_p_stk.emplace_back(v, p);  // keep [prices[last_v], prices[p]] interval to check overlapped
        }
        while (!v_p_stk.empty()) {
            auto last = v_p_stk.back(); v_p_stk.pop_back();
            profits.push_back(prices[last.second] - prices[last.first]);  // count [prices[last_v], prices[last_p]] interval
        }

        if (k == 0) {
            return 0;
        }
        if (k > static_cast<int>(profits.size())) {
            k = static_cast<int>(profits.size());
        } else {
            // Select top k profits of nonoverlapped intervals (descending order)
            nth_element_custom(profits, k - 1, [](int a, int b) { return a > b; });
        }
        long long result = 0;
        for (int i = 0; i < k; ++i) {
            result += profits[i];
        }
        return static_cast<int>(result);
    }
};

struct TestCase {
    int k;
    std::vector<int> prices;
};

int main() {
    std::vector<TestCase> tests = {
        {2, {3, 2, 6, 5, 0, 3}},
        {100, {1, 2, 3, 4, 5, 6}},
        {0, {1, 3, 2, 8, 4, 9}},
        {5, {5}},
        {3, {2, 4, 1, 7, 5, 3, 6, 4}},
        {4, {1, 5, 1, 5, 1, 5, 1}},
        {10, {9, 8, 7, 6, 5, 4, 3, 2, 1}},
        {2, {5, 1, 5, 1, 5}},
        {1, {1, 2, 3, 2, 5, 7, 2, 4, 9, 0}},
        {3, {3, 3, 5, 0, 0, 3, 1, 4, 2, 6, 4, 7, 2, 5, 1, 8}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& tc : tests) {
            int r = sol.maxProfit(tc.k, tc.prices);
            DoNotOptimize(r); 
        }
        //sink = checksum;
    }

    return 0;
}