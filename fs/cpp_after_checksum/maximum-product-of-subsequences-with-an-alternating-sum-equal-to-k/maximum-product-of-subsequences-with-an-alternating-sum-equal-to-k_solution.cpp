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
#include <numeric>
#include <utility>
#include <chrono>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const noexcept {
        return std::hash<long long>()((static_cast<long long>(p.first) << 32) ^ static_cast<unsigned long long>(p.second));
    }
};

class Solution {
public:
    int maxProduct(vector<int>& nums, int k, int limit) {
        long long total = 0;
        for (int x : nums) total += x;
        if (k > total || k < -total) {
            return -1;
        }
        using Key = pair<int, int>;
        unordered_map<Key, unordered_set<long long>, PairHash> dp;

        long long cap = static_cast<long long>(limit) + 1;

        for (int x : nums) {
            // deep copy dp to new_dp
            unordered_map<Key, unordered_set<long long>, PairHash> new_dp = dp;

            // start new subsequence with current element
            new_dp[{1, x}].insert(min(static_cast<long long>(x), cap));

            // extend existing subsequences
            for (const auto& kv : dp) {
                int p = kv.first.first;
                int total_sum = kv.first.second;
                const auto& products = kv.second;

                int new_p = p ^ 1;
                int new_total = total_sum + ((p == 0) ? x : -x);
                auto& target_set = new_dp[{new_p, new_total}];

                for (long long v : products) {
                    long long prod = v * static_cast<long long>(x);
                    if (prod > cap) prod = cap;
                    target_set.insert(prod);
                }
            }
            dp = std::move(new_dp);
        }

        long long result = -1;
        for (const auto& kv : dp) {
            int total_sum = kv.first.second;
            if (total_sum != k) continue;
            for (long long v : kv.second) {
                if (v <= limit) {
                    result = max(result, v);
                }
            }
        }
        return (result == -1) ? -1 : static_cast<int>(result);
    }
};
