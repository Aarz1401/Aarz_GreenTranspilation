#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <chrono>

using namespace std;

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums) {
        long long result = LLONG_MIN;
        long long curr = 0;
        long long mn = 0;
        long long mn0 = 0;
        unordered_map<long long, long long> mn1;  // default 0

        for (int x : nums) {
            long long xl = static_cast<long long>(x);
            curr += xl;
            result = max(result, curr - mn);
            long long& ref = mn1[xl];
            ref = min(ref, mn0) + xl;
            mn0 = min(mn0, curr);
            mn = min(mn, ref);
            mn = min(mn, mn0);
        }
        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<int>> tests;
    tests.reserve(10);

    // 1) All positive increasing
    tests.push_back({1, 2, 3, 4, 5, 6, 7});

    // 2) All negatives
    tests.push_back({-1, -2, -3, -4, -5, -6});

    // 3) Mixed with repeated negatives (removal beneficial)
    tests.push_back({3, -1, 3, 3, -1, 3, -1, 3});

    // 4) Zeros interleaved with positives and a negative
    tests.push_back({0, 1, 0, 2, 0, 3, 0, -2, 0, 4, 0});

    // 5) Values near integer extremes (kept moderate to avoid overflow in accumulation)
    tests.push_back({INT_MAX / 2, -1, 2, -3, INT_MIN / 2 + 1, 4, -5, 6});

    // 6) Single element
    tests.push_back({5});

    // 7) Alternating large positive and negative repeated element
    tests.push_back({1000000, -1000000, 1000000, -1000000, 1000000, -1000000, 1000000});

    // 8) Repeated negative element dominant
    tests.push_back({-5, -1, -5, -1, -5, -1, -5});

    // 9) Classic mixed case
    tests.push_back({-2, 1, -3, 4, -1, 2, 1, -5, 4});

    // 10) Many duplicates of one negative with positives
    tests.push_back({10, -5, -5, -5, 10, -5, 10, -5, 10});

    Solution sol;
    long long checksum = 0;

    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::microseconds;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            checksum += sol.maxSubarraySum(t);
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed microseconds: " << elapsed_us << "\n";

    return 0;
}