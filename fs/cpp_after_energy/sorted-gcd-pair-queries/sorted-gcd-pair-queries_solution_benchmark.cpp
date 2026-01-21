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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
private:
    vector<int> gcdValuesImpl(const vector<int>& nums, const vector<long long>& queries) {
        if (nums.empty()) return vector<int>(queries.size(), 0);
        int r = *max_element(nums.begin(), nums.end());
        vector<long long> freq(r + 1, 0);
        for (int x : nums) {
            ++freq[x];
        }
        vector<long long> cnt2(r + 1, 0);
        for (int g = r; g >= 1; --g) {
            long long c = 0;
            for (int ng = g; ng <= r; ng += g) {
                c += freq[ng];
            }
            long long s = 0;
            for (int ng = g + g; ng <= r; ng += g) {
                s += cnt2[ng];
            }
            cnt2[g] = c * (c - 1) / 2 - s;
        }
        vector<long long> prefix(r + 2, 0);
        for (int i = 0; i <= r; ++i) {
            prefix[i + 1] = prefix[i] + cnt2[i];
        }
        vector<int> result;
        result.reserve(queries.size());
        for (long long q : queries) {
            auto it = upper_bound(prefix.begin(), prefix.end(), q);
            int idx = static_cast<int>(it - prefix.begin()) - 1;
            result.push_back(idx);
        }
        return result;
    }
public:
    vector<int> gcdValues(vector<int>& nums, vector<int>& queries) {
        vector<long long> qll(queries.size());
        for (size_t i = 0; i < queries.size(); ++i) qll[i] = static_cast<long long>(queries[i]);
        return gcdValuesImpl(nums, qll);
    }
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        return gcdValuesImpl(nums, queries);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Test 1: small array
    vector<int> nums1 = {1, 2, 3, 4, 5};
    vector<int> q1 = {0, 1, 3, 6, 9, 10};

    // Test 2: moderately sized with varied values
    vector<int> nums2;
    for (int i = 1; i <= 60; ++i) nums2.push_back((i * 7) % 101 + 1);
    vector<int> q2 = {0, 1, 10, 100, 500, 1000};

    // Test 3: all same numbers
    vector<int> nums3(40, 7);
    vector<long long> q3 = {0LL, 100LL, 779LL, 780LL, 10000LL};

    // Test 4: primes
    vector<int> nums4 = {
        2,3,5,7,11,13,17,19,23,29,
        31,37,41,43,47,53,59,61,67,71,
        73,79,83,89,97,101,103,107,109,113,
        127,131,137,139,149,151,157,163,167,173,
        179,181,191,193,197,199,211,223,227,229
    };
    vector<int> q4 = {0, 1, 100, 1769};

    // Test 5: multiples of 6
    vector<int> nums5;
    for (int i = 1; i <= 100; ++i) nums5.push_back(i * 6);
    vector<long long> q5 = {0LL, 10LL, 1000LL, 3000LL, 4950LL};

    // Test 6: empty nums
    vector<int> nums6;
    vector<int> q6 = {0, 1, 2, 3, 4, 5};

    // Test 7: single element
    vector<int> nums7 = {42};
    vector<long long> q7 = {0LL, 1LL, 2LL, 3LL, 4LL, 5LL, 100LL};

    // Test 8: high values with moderate r
    vector<int> nums8 = {10000, 9999, 9998, 9997, 9996, 9995, 5000, 2500, 1250};
    vector<int> q8 = {0, 1, 2, 3, 4, 5, 10, 20, 30};

    // Test 9: 1..200
    vector<int> nums9;
    for (int i = 1; i <= 200; ++i) nums9.push_back(i);
    vector<long long> q9 = {0LL, 50LL, 1000LL, 10000LL, 19900LL};

    // Test 10: patterned 300 numbers with r up to 5000
    vector<int> nums10;
    for (int i = 1; i <= 300; ++i) nums10.push_back((i * 37) % 5000 + 1);
    vector<int> q10 = {0, 10, 100, 1000, 2000, 40000};

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        auto r1 = sol.gcdValues(nums1, q1);
        for (int v : r1) checksum += v;

        auto r2 = sol.gcdValues(nums2, q2);
        for (int v : r2) checksum += v;

        auto r3 = sol.gcdValues(nums3, q3);
        for (int v : r3) checksum += v;

        auto r4 = sol.gcdValues(nums4, q4);
        for (int v : r4) checksum += v;

        auto r5 = sol.gcdValues(nums5, q5);
        for (int v : r5) checksum += v;

        auto r6 = sol.gcdValues(nums6, q6);
        for (int v : r6) checksum += v;

        auto r7 = sol.gcdValues(nums7, q7);
        for (int v : r7) checksum += v;

        auto r8 = sol.gcdValues(nums8, q8);
        for (int v : r8) checksum += v;

        auto r9 = sol.gcdValues(nums9, q9);
        for (int v : r9) checksum += v;

        auto r10 = sol.gcdValues(nums10, q10);
        for (int v : r10) checksum += v;
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}