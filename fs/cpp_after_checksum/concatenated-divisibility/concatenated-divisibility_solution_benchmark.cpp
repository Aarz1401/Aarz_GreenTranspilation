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

using namespace std;

class Solution {
public:
    vector<int> concatenatedDivisibility(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> lookup(n);
        auto length = [](int x) -> int {
            if (x == 0) return 1;
            if (x < 0) x = -x;
            int l = 0;
            while (x) {
                ++l;
                x /= 10;
            }
            return max(l, 1);
        };
        for (int i = 0; i < n; ++i) {
            lookup[i] = length(nums[i]);
        }
        int mx = 0;
        for (int l : lookup) mx = max(mx, l);

        vector<int> pow10(mx + 1, 0);
        pow10[0] = 1 % k;
        for (int i = 0; i < mx; ++i) {
            pow10[i + 1] = static_cast<int>((1LL * pow10[i] * 10) % k);
        }

        int total = 1 << n;
        vector<vector<char>> dp(total, vector<char>(k, 0));
        dp[total - 1][0] = 1;

        for (int mask = total - 2; mask >= 0; --mask) {
            for (int r = 0; r < k; ++r) {
                for (int i = 0; i < n; ++i) {
                    if (mask & (1 << i)) continue;
                    int l = lookup[i];
                    int add = ((nums[i] % k) + k) % k;
                    int newr = static_cast<int>(( (1LL * r * pow10[l]) % k + add ) % k);
                    if (dp[mask | (1 << i)][newr]) {
                        dp[mask][r] = 1;
                        break;
                    }
                }
            }
        }

        vector<int> result;
        if (!dp[0][0]) return result;

        vector<pair<int, int>> order;
        order.reserve(n);
        for (int i = 0; i < n; ++i) {
            order.emplace_back(nums[i], i);
        }
        sort(order.begin(), order.end());

        int mask = 0;
        int r = 0;
        for (int step = 0; step < n; ++step) {
            for (const auto& p : order) {
                int i = p.second;
                if (mask & (1 << i)) continue;
                int l = lookup[i];
                int add = ((nums[i] % k) + k) % k;
                int newr = static_cast<int>(( (1LL * r * pow10[l]) % k + add ) % k);
                if (dp[mask | (1 << i)][newr]) {
                    result.push_back(nums[i]);
                    mask |= (1 << i);
                    r = newr;
                    break;
                }
            }
        }
        return result;
    }
};

struct TestCase {
    vector<int> nums;
    int k;
};

int main() {
    vector<TestCase> tests;
    tests.push_back({{1, 2}, 3});                           // simple small case
    tests.push_back({{-1, 2, -3}, 7});                      // includes negatives
    tests.push_back({{0, 0, 5}, 5});                        // zeros with divisibility
    tests.push_back({{12, 34, 56}, 11});                    // multi-digit numbers
    tests.push_back({{123, 4, 56, 7}, 13});                 // mixed lengths
    tests.push_back({{10, 10, 10}, 10});                    // duplicates
    tests.push_back({{0}, 1});                              // single zero, k=1
    tests.push_back({{-999}, 3});                           // single negative divisible
    tests.push_back({{8, 80, 800, 5, 50, 500, 7, 70}, 9});  // larger set
    tests.push_back({{-12, 3, -45, 6, 789}, 37});           // mixed signs and sizes

    Solution solver;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < tests.size(); ++t) {
            auto res = solver.concatenatedDivisibility(tests[t].nums, tests[t].k);
            uint64_t local = 0;
            for (int v : res) {
                local = local * 1315423911ull + static_cast<uint64_t>(v + 1000003);
            }
            checksum ^= (local + static_cast<uint64_t>(tests[t].k) * 2654435761ull + static_cast<uint64_t>(t));
            checksum += res.size();
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}