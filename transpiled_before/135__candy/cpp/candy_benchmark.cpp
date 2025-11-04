#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <chrono>

class Solution {
public:
    // Time:  O(n)
    // Space: O(n)
    int candy(std::vector<int>& ratings) {
        int n = static_cast<int>(ratings.size());
        if (n == 0) return 0;
        
        std::vector<int> candies(n, 1);
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] = candies[i - 1] + 1;
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1]) {
                candies[i] = candies[i + 1] + 1;
            }
        }
        return std::accumulate(candies.begin(), candies.end(), 0);
    }
};

int main() {
    // Prepare 10 diverse test inputs
    std::vector<std::vector<int>> tests;
    tests.reserve(10);

    // 1) Empty input
    tests.push_back({});

    // 2) Single element
    tests.push_back({5});

    // 3) Strictly increasing
    tests.push_back({1,2,3,4,5,6,7,8,9});

    // 4) Strictly decreasing
    tests.push_back({9,8,7,6,5,4,3,2,1});

    // 5) All equal
    tests.push_back(std::vector<int>(10, 7));

    // 6) Peaks and valleys with plateaus
    tests.push_back({1,3,2,2,1,2,3,1});

    // 7) Alternating high/low
    tests.push_back({1,0,1,0,1,0,1,0,1,0});

    // 8) Plateau then drop then rise
    tests.push_back({2,2,2,2,1,2,2,3,3,2,1,1,2});

    // 9) Deterministic pseudo-random long input
    {
        std::vector<int> v9(2048);
        for (int i = 0; i < static_cast<int>(v9.size()); ++i) {
            v9[i] = (i * 37 + 13) % 100;
        }
        tests.push_back(std::move(v9));
    }

    // 10) Triangular wave pattern
    {
        std::vector<int> v10;
        v10.reserve(1000);
        for (int i = 0; i < 1000; ++i) {
            int phase = i % 40;
            int val = (phase < 20) ? phase : 39 - phase; // 0..19..0
            v10.push_back(val);
        }
        tests.push_back(std::move(v10));
    }

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            checksum += sol.candy(t);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << std::endl;
    std::cout << "Elapsed time (microseconds): " << elapsed_us << std::endl;

    return 0;
}