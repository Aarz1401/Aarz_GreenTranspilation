#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <random>
#include <limits>
#include <chrono>

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

// Time:  O(k * n)
// Space: O(k)
class Solution2 {
public:
    int maxProfit(int k, std::vector<int>& prices) {
        auto maxAtMostNPairsProfit = [&](const std::vector<int>& sprices) -> int {
            long long profit = 0;
            for (size_t i = 0; i + 1 < sprices.size(); ++i) {
                profit += std::max(0, sprices[i + 1] - sprices[i]);
            }
            return static_cast<int>(profit);
        };

        auto maxAtMostKPairsProfit = [&](const std::vector<int>& p, int kk) -> int {
            std::vector<long long> max_buy(kk + 1, std::numeric_limits<long long>::min() / 4);
            std::vector<long long> max_sell(kk + 1, 0);
            for (int price : p) {
                for (int j = 1; j <= kk; ++j) {
                    max_buy[j]  = std::max(max_buy[j],  max_sell[j - 1] - price);
                    max_sell[j] = std::max(max_sell[j], max_buy[j] + price);
                }
            }
            return static_cast<int>(max_sell[kk]);
        };

        if (k >= static_cast<int>(prices.size()) / 2) {
            return maxAtMostNPairsProfit(prices);
        }
        return maxAtMostKPairsProfit(prices, k);
    }
};

int main() {
    // Prepare 10 diverse test cases
    std::vector<std::vector<int>> pricesList;
    std::vector<int> ks;
    pricesList.reserve(10);
    ks.reserve(10);

    // 1. Empty prices
    pricesList.push_back({});
    ks.push_back(3);

    // 2. Single element
    pricesList.push_back({5});
    ks.push_back(1);

    // 3. Strictly increasing
    pricesList.push_back({1, 2, 3, 4, 5});
    ks.push_back(10);

    // 4. Strictly decreasing
    pricesList.push_back({5, 4, 3, 2, 1});
    ks.push_back(2);

    // 5. Mixed typical case
    pricesList.push_back({3, 2, 6, 5, 0, 3});
    ks.push_back(2);

    // 6. All equal elements
    pricesList.push_back({2, 2, 2, 2, 2, 2});
    ks.push_back(100);

    // 7. Multiple rising peaks
    pricesList.push_back({1, 7, 2, 8, 3, 9, 4, 10, 5, 11});
    ks.push_back(4);

    // 8. Alternating high-low
    pricesList.push_back({10, 1, 10, 1, 10, 1, 10, 1});
    ks.push_back(2);

    // 9. Long repeating up-down pattern (size ~2000)
    {
        std::vector<int> pattern = {1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10};
        std::vector<int> longPattern;
        longPattern.reserve(2000);
        while (longPattern.size() < 2000) {
            longPattern.insert(longPattern.end(), pattern.begin(), pattern.end());
        }
        longPattern.resize(2000);
        pricesList.push_back(std::move(longPattern));
        ks.push_back(500);
    }

    // 10. Pseudo-random-like large sequence (size 3000)
    {
        std::vector<int> largeSeq;
        largeSeq.reserve(3000);
        uint32_t x = 123456789u;
        for (int i = 0; i < 3000; ++i) {
            // Linear Congruential Generator for determinism
            x = 1664525u * x + 1013904223u;
            largeSeq.push_back(static_cast<int>(x % 100000u));
        }
        pricesList.push_back(std::move(largeSeq));
        ks.push_back(1000);
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        checksum += sol.maxProfit(ks[0], pricesList[0]);
        checksum += sol.maxProfit(ks[1], pricesList[1]);
        checksum += sol.maxProfit(ks[2], pricesList[2]);
        checksum += sol.maxProfit(ks[3], pricesList[3]);
        checksum += sol.maxProfit(ks[4], pricesList[4]);
        checksum += sol.maxProfit(ks[5], pricesList[5]);
        checksum += sol.maxProfit(ks[6], pricesList[6]);
        checksum += sol.maxProfit(ks[7], pricesList[7]);
        checksum += sol.maxProfit(ks[8], pricesList[8]);
        checksum += sol.maxProfit(ks[9], pricesList[9]);
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_ms = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}