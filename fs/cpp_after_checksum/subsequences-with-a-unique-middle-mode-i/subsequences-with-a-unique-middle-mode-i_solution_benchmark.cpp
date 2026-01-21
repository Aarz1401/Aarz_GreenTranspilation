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
    int subsequencesWithMiddleMode(vector<int>& nums) {
        const long long MOD = 1000000007LL;
        int n = nums.size();
        unordered_map<int, long long> left, right;
        left.reserve(n * 2);
        right.reserve(n * 2);
        for (int x : nums) {
            right[x] += 1;
        }

        auto C2 = [](long long x) -> __int128 {
            return (__int128)x * (x - 1) / 2;
        };

        long long left_x_sq = 0;             // sum(left[x]^2 for x != v)
        long long right_x_sq = 0;            // sum(right[x]^2 for x != v)
        long long left_x_right_x = 0;        // sum(left[x]*right[x] for x != v)
        long long left_x_sq_right_x = 0;     // sum(left[x]^2*right[x] for x != v)
        long long left_x_right_x_sq = 0;     // sum(left[x]*right[x]^2 for x != v)

        for (const auto& kv : right) {
            long long c = kv.second;
            right_x_sq += c * c;
        }

        __int128 result = 0;

        for (int i = 0; i < n; ++i) {
            int v = nums[i];
            long long lv = left[v];
            long long rv_before = right[v];

            left_x_sq -= lv * lv;
            right_x_sq -= rv_before * rv_before;
            left_x_right_x -= lv * rv_before;
            left_x_sq_right_x -= lv * lv * rv_before;
            left_x_right_x_sq -= lv * rv_before * rv_before;

            right[v] = rv_before - 1;
            long long rv = right[v];

            long long l = i;
            long long r = n - (i + 1);

            // all possibles
            result += C2(l) * C2(r);

            // only mid is a
            long long l_minus_lv = l - lv;
            long long r_minus_rv = r - rv;
            result -= C2(l_minus_lv) * C2(r_minus_rv);

            // bb/a/ac
            {
                __int128 t1 = (__int128)(left_x_sq - l_minus_lv) * (r_minus_rv) - (__int128)(left_x_sq_right_x - left_x_right_x);
                result -= t1 * rv / 2;
            }
            // ac/a/bb
            {
                __int128 t2 = (__int128)(right_x_sq - r_minus_rv) * (l_minus_lv) - (__int128)(left_x_right_x_sq - left_x_right_x);
                result -= t2 * lv / 2;
            }
            // ab/a/bc
            result -= (__int128)lv * left_x_right_x * r_minus_rv - (__int128)lv * left_x_right_x_sq;
            // bc/a/ab
            result -= (__int128)rv * left_x_right_x * l_minus_lv - (__int128)rv * left_x_sq_right_x;
            // bb/a/ab
            result -= (__int128)rv * (left_x_sq_right_x - left_x_right_x) / 2;
            // ab/a/bb
            result -= (__int128)lv * (left_x_right_x_sq - left_x_right_x) / 2;

            left[v] = lv + 1;
            long long lv_new = lv + 1;
            long long rv_now = rv;

            left_x_sq += lv_new * lv_new;
            right_x_sq += rv_now * rv_now;
            left_x_right_x += lv_new * rv_now;
            left_x_sq_right_x += lv_new * lv_new * rv_now;
            left_x_right_x_sq += lv_new * rv_now * rv_now;
        }

        long long ans = (long long)((result % MOD + MOD) % MOD);
        return (int)ans;
    }
};

int main() {
    // Prepare 10 diverse test cases
    vector<vector<int>> testCases;
    testCases.reserve(10);

    // 1) Empty array
    vector<int> tc1;
    testCases.push_back(tc1);

    // 2) Single element
    vector<int> tc2 = {42};
    testCases.push_back(tc2);

    // 3) Two different elements
    vector<int> tc3 = {1, 2};
    testCases.push_back(tc3);

    // 4) All identical elements
    vector<int> tc4(50, 5);
    testCases.push_back(tc4);

    // 5) Alternating two values
    vector<int> tc5;
    tc5.reserve(60);
    for (int i = 0; i < 60; ++i) tc5.push_back((i % 2) ? 2 : 1);
    testCases.push_back(tc5);

    // 6) Increasing sequence
    vector<int> tc6;
    tc6.reserve(100);
    for (int i = 1; i <= 100; ++i) tc6.push_back(i);
    testCases.push_back(tc6);

    // 7) Decreasing sequence
    vector<int> tc7;
    tc7.reserve(200);
    for (int i = 200; i >= 1; --i) tc7.push_back(i);
    testCases.push_back(tc7);

    // 8) Pseudo-random with quadratic formula modulo 25 (lots of duplicates)
    vector<int> tc8;
    tc8.reserve(200);
    for (int i = 0; i < 200; ++i) {
        long long val = (1LL * i * i + 7LL * i + 13LL) % 25LL;
        tc8.push_back((int)val);
    }
    testCases.push_back(tc8);

    // 9) Extremes and small values repeated
    vector<int> tc9;
    tc9.reserve(100);
    for (int i = 0; i < 25; ++i) {
        tc9.push_back(INT_MAX);
        tc9.push_back(INT_MIN);
        tc9.push_back(0);
        tc9.push_back(-1);
    }
    testCases.push_back(tc9);

    // 10) Linear congruential-like sequence modulo 50
    vector<int> tc10;
    tc10.reserve(300);
    for (int i = 0; i < 300; ++i) {
        tc10.push_back((i * 37 + 23) % 50);
    }
    testCases.push_back(tc10);

    Solution sol;

    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < testCases.size(); ++i) {
            int res = sol.subsequencesWithMiddleMode(testCases[i]);
            // Mix into checksum to avoid optimization
            checksum ^= (unsigned long long)res + 0x9e3779b97f4a7c15ull + (checksum << 6) + (checksum >> 2);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}