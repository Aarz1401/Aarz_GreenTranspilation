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
#include <limits>
#include <array>
#include <utility>
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
    // Generate 10 diverse test inputs
    vector<vector<int>> tests;
    vector<int> ks;

    // 0: Empty array
    tests.push_back({});
    ks.push_back(0);

    // 1: Single element
    tests.push_back({1});
    ks.push_back(0);

    // 2: Small odds
    tests.push_back({3, 5, 7, 9, 11, 13, 15, 17});
    ks.push_back(1);

    // 3: Powers of two
    {
        vector<int> v;
        for (int i = 1; i <= 16; ++i) v.push_back(1 << i);
        tests.push_back(std::move(v));
        ks.push_back(4);
    }

    // 4: Mixed even composites
    tests.push_back({6, 10, 14, 22, 26, 30, 42, 60, 84, 98, 126, 150, 210, 330, 510, 1022});
    ks.push_back(3);

    // 5: Repeated elements with same 2-exponent
    {
        vector<int> v(24, 12); // 12 = 3 * 2^2
        tests.push_back(std::move(v));
        ks.push_back(2);
    }

    // 6: Sequential numbers
    {
        vector<int> v;
        for (int i = 1; i <= 40; ++i) v.push_back(i);
        tests.push_back(std::move(v));
        ks.push_back(5);
    }

    // 7: Deterministic pseudo-random with variable 2-exponent
    {
        vector<int> v;
        for (int i = 1; i <= 64; ++i) {
            uint32_t val = (static_cast<uint32_t>(i) * 97u) ^ (static_cast<uint32_t>(i) * 131u);
            int base = static_cast<int>(val % 1000000u) + 1;
            base <<= (i % 3);
            v.push_back(base);
        }
        tests.push_back(std::move(v));
        ks.push_back(0);
    }

    // 8: Primes (including 2)
    tests.push_back({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71});
    ks.push_back(2);

    // 9: Larger structured array with varying 2-exponents
    {
        vector<int> v;
        for (int i = 1; i <= 96; ++i) {
            int val = (i + 1) * (i % 7 + 1) * (1 << (i % 5)) + (i % 3);
            if (val <= 0) val = i + 1;
            v.push_back(val);
        }
        tests.push_back(std::move(v));
        ks.push_back(7);
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        // Run all test cases each iteration
        for (size_t t = 0; t < tests.size(); ++t) {
            vector<int> nums = tests[t]; // copy because function mutates nums
            checksum += sol.maxGCDScore(nums, ks[t]);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    double elapsed_ms = static_cast<double>(elapsed_ns) / 1e6;

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}