#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

// Time:  O(nlogn)
// Space: O(1)
class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // Sort by width asc; if same width, height desc
        sort(envelopes.begin(), envelopes.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 if (a[0] == b[0]) return a[1] > b[1];
                 return a[0] < b[0];
             });

        vector<int> result;
        for (const auto& envelope : envelopes) {
            insert(result, envelope[1]);
        }
        return static_cast<int>(result.size());
    }

private:
    void insert(vector<int>& result, int target) {
        auto it = lower_bound(result.begin(), result.end(), target);
        if (it == result.end()) {
            result.emplace_back(target);
        } else {
            *it = target;
        }
    }
};

int main() {
    // Prepare 10 diverse test inputs
    vector<vector<int>> base1; // empty

    vector<vector<int>> base2 = {
        {5, 4}
    };

    vector<vector<int>> base3; // all duplicates
    for (int i = 0; i < 8; ++i) {
        base3.push_back({2, 2});
    }

    vector<vector<int>> base4; // strictly increasing chain
    for (int i = 1; i <= 20; ++i) {
        base4.push_back({i, i});
    }

    vector<vector<int>> base5 = { // mixed small sample
        {5, 4}, {6, 4}, {6, 7}, {2, 3}, {1, 1}, {7, 8},
        {7, 7}, {8, 9}, {5, 5}, {5, 3}, {9, 6}, {10, 10}
    };

    vector<vector<int>> base6; // same width, varying heights
    for (int h = 1; h <= 30; ++h) {
        base6.push_back({3, h});
    }

    vector<vector<int>> base7; // strictly decreasing widths/heights
    for (int i = 30; i >= 1; --i) {
        base7.push_back({i, i});
    }

    vector<vector<int>> base8 = { // tie-breaker heavy (many equal widths)
        {4, 5}, {4, 6}, {4, 7}, {4, 4},
        {5, 3}, {5, 5}, {5, 4},
        {6, 7}, {6, 6}, {6, 8},
        {7, 1}, {7, 2}, {7, 3}
    };

    // Deterministic random dataset
    vector<vector<int>> base9;
    {
        mt19937 rng(123456);
        uniform_int_distribution<int> distW(1, 10000);
        uniform_int_distribution<int> distH(1, 10000);
        base9.reserve(200);
        for (int i = 0; i < 200; ++i) {
            base9.push_back({distW(rng), distH(rng)});
        }
    }

    vector<vector<int>> base10; // ascending width, descending height (LIS of 1)
    {
        int N = 300;
        base10.reserve(N);
        for (int i = 1; i <= N; ++i) {
            base10.push_back({i, N - i + 1});
        }
    }

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        // Copy each base input to avoid in-place modification by sort
        vector<vector<int>> t1 = base1;
        vector<vector<int>> t2 = base2;
        vector<vector<int>> t3 = base3;
        vector<vector<int>> t4 = base4;
        vector<vector<int>> t5 = base5;
        vector<vector<int>> t6 = base6;
        vector<vector<int>> t7 = base7;
        vector<vector<int>> t8 = base8;
        vector<vector<int>> t9 = base9;
        vector<vector<int>> t10 = base10;

        checksum += sol.maxEnvelopes(t1);
        checksum += sol.maxEnvelopes(t2);
        checksum += sol.maxEnvelopes(t3);
        checksum += sol.maxEnvelopes(t4);
        checksum += sol.maxEnvelopes(t5);
        checksum += sol.maxEnvelopes(t6);
        checksum += sol.maxEnvelopes(t7);
        checksum += sol.maxEnvelopes(t8);
        checksum += sol.maxEnvelopes(t9);
        checksum += sol.maxEnvelopes(t10);
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << '\n';
    cout << "Elapsed time (ns): " << elapsed_ns << '\n';

    return 0;
}