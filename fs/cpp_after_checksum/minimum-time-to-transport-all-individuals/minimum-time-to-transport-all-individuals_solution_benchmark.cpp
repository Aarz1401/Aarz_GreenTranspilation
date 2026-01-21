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
#include <tuple>
#include <functional>
#include <chrono>
#include <iomanip>
using namespace std;

class Solution {
public:
    // dijkstra's algorithm, submask enumeration
    double minTime(int n, int k, int m, vector<int>& time, vector<double>& mul) {
        auto INF = numeric_limits<double>::infinity();

        int total_masks = 1 << n;

        // Precompute popcount for better performance
        vector<int> popcount(total_masks, 0);
        for (int i = 1; i < total_masks; ++i) {
            popcount[i] = popcount[i >> 1] + (i & 1);
        }

        // Precompute lookup: max(time[i]) over i in mask
        vector<int> lookup(total_masks, 0);
        for (int mask = 1; mask < total_masks; ++mask) {
            int mx = 0;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) {
                    mx = max(mx, time[i]);
                }
            }
            lookup[mask] = mx;
        }

        // dist[r][s][mask]
        vector<vector<vector<double>>> dist(2, vector<vector<double>>(m, vector<double>(total_masks, INF)));
        dist[0][0][total_masks - 1] = 0.0;

        using T = tuple<double, int, int, int>;
        priority_queue<T, vector<T>, greater<T>> min_heap;
        min_heap.emplace(0.0, 0, 0, total_masks - 1);

        // Helper to update states
        auto update = [&](double d, int r, int s, int mask, int submask) {
            double t = static_cast<double>(lookup[submask]) * mul[s];
            int nr = r ^ 1;
            int ns = (s + static_cast<int>(t)) % m;
            int new_mask = mask ^ submask;
            double nd = d + t;
            if (dist[nr][ns][new_mask] > nd) {
                dist[nr][ns][new_mask] = nd;
                min_heap.emplace(nd, nr, ns, new_mask);
            }
        };

        while (!min_heap.empty()) {
            auto [d, r, s, mask] = min_heap.top();
            min_heap.pop();
            if (d != dist[r][s][mask]) {
                continue;
            }
            if (mask == 0) {
                return d;
            }
            if (r == 0) {
                int submask = mask;
                while (submask) {  // enumerate submasks
                    if (popcount[submask] <= k) {
                        update(d, r, s, mask, submask);
                    }
                    submask = (submask - 1) & mask;
                }
            } else {
                for (int i = 0; i < n; ++i) {
                    if (mask & (1 << i)) {
                        continue;
                    }
                    update(d, r, s, mask, 1 << i);
                }
            }
        }
        return -1.0;
    }
};

struct TestCase {
    int n;
    int k;
    int m;
    vector<int> time;
    vector<double> mul;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);
    tests.push_back(TestCase{1, 1, 1, {5}, {1.0}});
    tests.push_back(TestCase{2, 1, 2, {3, 7}, {0.8, 1.2}});
    tests.push_back(TestCase{3, 2, 3, {4, 2, 9}, {1.0, 1.5, 0.5}});
    tests.push_back(TestCase{4, 2, 4, {2, 5, 1, 7}, {0.9, 1.1, 1.3, 0.7}});
    tests.push_back(TestCase{5, 3, 3, {8, 3, 6, 2, 9}, {1.0, 0.95, 1.2}});
    tests.push_back(TestCase{6, 2, 5, {5, 4, 7, 3, 8, 6}, {1.2, 0.8, 1.0, 1.5, 0.6}});
    tests.push_back(TestCase{7, 3, 2, {9, 1, 4, 7, 2, 5, 3}, {1.1, 0.9}});
    tests.push_back(TestCase{8, 4, 4, {6, 2, 9, 1, 7, 3, 8, 5}, {1.0, 0.75, 1.25, 0.5}});
    tests.push_back(TestCase{9, 3, 6, {3, 6, 1, 8, 2, 7, 4, 9, 5}, {0.9, 1.05, 1.2, 0.8, 1.3, 0.7}});
    tests.push_back(TestCase{5, 1, 7, {10, 3, 8, 2, 6}, {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1}});

    Solution sol;
    double checksum = 0.0;

    using chrono::high_resolution_clock;
    using chrono::duration;
    using chrono::duration_cast;

    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.minTime(tc.n, tc.k, tc.m, tc.time, tc.mul);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<chrono::duration<double, std::milli>>(end - start).count();

    cout << fixed << setprecision(6);
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed << "\n";

    return 0;
}