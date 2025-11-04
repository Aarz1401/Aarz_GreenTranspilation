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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<int>> numsList = {
        {1},                 // Single element
        {2, 3},              // Two positives, k = -1
        {-2, 4, -1},         // Mix of negatives and positives
        {0, 5, 6},           // Contains zero
        {10, 9, 8},          // Large products exceeding small limit
        {1, 2, 3},           // k out of range triggers early return
        {2, 5},              // Negative k
        {1, 1, 1, 1},        // Repeated elements
        {0, 1},              // Zero with limit zero
        {7, -3, 2}           // Early bound fail with negatives present
    };

    vector<int> ks = {
        1,    // For {1}
        -1,   // For {2,3}
        4,    // For {-2,4,-1}
        0,    // For {0,5,6}
        1,    // For {10,9,8}
        100,  // For {1,2,3} early return
        -3,   // For {2,5}
        0,    // For {1,1,1,1}
        0,    // For {0,1}
        7     // For {7,-3,2} early bound fail
    };

    vector<int> limits = {
        10,   // For {1}
        10,   // For {2,3}
        100,  // For {-2,4,-1}
        100,  // For {0,5,6}
        20,   // For {10,9,8}
        100,  // For {1,2,3}
        100,  // For {2,5}
        10,   // For {1,1,1,1}
        0,    // For {0,1}
        5     // For {7,-3,2}
    };

    Solution sol;

    volatile long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < numsList.size(); ++t) {
            int res = sol.maxProduct(numsList[t], ks[t], limits[t]);
            checksum += res;
        }
    }
    auto end = chrono::high_resolution_clock::now();

    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}