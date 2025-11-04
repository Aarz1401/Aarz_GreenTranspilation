#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <array>
#include <utility>
#include <climits>
#include <numeric>
#include <chrono>
#include <cstdint>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const noexcept {
        return (static_cast<uint64_t>(static_cast<uint32_t>(p.first)) << 32) ^ static_cast<uint32_t>(p.second);
    }
};

class Solution {
public:
    long long maxGCDScore(vector<int>& nums, int k) {
        int n = static_cast<int>(nums.size());
        vector<int> lookup(n, 0);
        for (int i = 0; i < n; ++i) {
            while ((nums[i] & 1) == 0) {
                nums[i] >>= 1;
                lookup[i] += 1;
            }
        }
        int maxe = 0;
        for (int e : lookup) maxe = max(maxe, e);
        vector<vector<int>> lookup2(maxe + 1);
        for (int i = 0; i < n; ++i) {
            lookup2[lookup[i]].push_back(i);
        }

        long long result = 0;
        unordered_map<pair<int, int>, array<int, 2>, PairHash> dp;

        for (int i = 0; i < n; ++i) {
            unordered_map<pair<int, int>, array<int, 2>, PairHash> new_dp;
            // Initialize state starting at i
            pair<int, int> base_key = {nums[i], lookup[i]};
            new_dp.emplace(base_key, array<int,2>{i, i});

            // Transition from previous states
            for (const auto& kv : dp) {
                int g = kv.first.first;
                int e = kv.first.second;
                int v0 = kv.second[0];

                int ng = std::gcd(g, nums[i]);
                int ne = min(e, lookup[i]);
                pair<int,int> key = {ng, ne};

                auto it = new_dp.find(key);
                if (it == new_dp.end()) {
                    it = new_dp.emplace(key, array<int,2>{INT_MAX/4, INT_MAX/4}).first;
                }
                // Update earliest left index
                it->second[0] = min(it->second[0], v0);

                // Compute left index to ensure occurrences of exponent ne in [left..i] <= k
                const vector<int>& idxs = lookup2[ne];
                int left_idx = static_cast<int>(lower_bound(idxs.begin(), idxs.end(), v0) - idxs.begin());
                int right_idx = static_cast<int>(upper_bound(idxs.begin(), idxs.end(), i) - idxs.begin()) - 1;
                int cnt = (right_idx >= left_idx) ? (right_idx - left_idx + 1) : 0;

                int candidateLeft;
                if (cnt <= k) {
                    candidateLeft = v0;
                } else {
                    candidateLeft = idxs[right_idx - k] + 1;
                }
                it->second[1] = min(it->second[1], candidateLeft);
            }

            dp = std::move(new_dp);

            // Update result using current states ending at i
            for (const auto& kv : dp) {
                int g = kv.first.first;
                int e = kv.first.second;
                int v0 = kv.second[0];
                int v1 = kv.second[1];

                long long term1 = 1LL * g * (i - v0 + 1);
                term1 <<= e;
                result = max(result, term1);

                if (v1 <= i) {
                    long long term2 = 1LL * g * (i - v1 + 1);
                    term2 <<= (e + 1);
                    result = max(result, term2);
                }
            }
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<pair<vector<int>, int>> tests;
    tests.push_back({{1}, 0});                                      // Single odd element
    tests.push_back({{1048576}, 0});                                // Single element with high power of two (2^20)
    tests.push_back({{12, 40}, 0});                                 // Two evens with different exponents of two
    tests.push_back({{6, 15, 10, 3, 14}, 1});                       // Mixed even/odd with k=1
    tests.push_back({{3, 5, 7, 11, 13, 17}, 0});                    // All odd primes
    tests.push_back({{18, 18, 18, 18}, 2});                         // Repeated values, k=2
    tests.push_back({{2, 4, 8, 16, 32, 64}, 1});                    // Increasing powers of two
    tests.push_back({{1000000007, 1000000007, 1000000007}, 10});    // Large odd numbers, k > count
    tests.push_back({{45, 75, 105, 210, 420}, 3});                  // Diverse composites with shared factors
    tests.push_back({{24, 36, 48, 60, 72, 84, 96, 108}, 2});        // Larger array with varied even exponents

    Solution solver;

    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    unsigned long long total = 0;
    const int iterations = 1000;

    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<int> nums = tests[i].first; // copy because the algorithm mutates nums
            int k = tests[i].second;
            total += static_cast<unsigned long long>(solver.maxGCDScore(nums, k));
        }
    }

    auto end = clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Total result: " << total << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}