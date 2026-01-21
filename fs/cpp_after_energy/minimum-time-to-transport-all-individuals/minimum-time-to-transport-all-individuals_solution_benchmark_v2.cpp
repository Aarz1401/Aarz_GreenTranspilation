#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
#include <limits>
#include <functional>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

volatile int sink = 0;

int main() {
    vector<TestCase> tests = {
        {1, 1, 2, {5}, {1.0, 0.5}},
        {2, 2, 3, {3, 7}, {1.0, 1.2, 0.8}},
        {3, 2, 4, {2, 4, 6}, {1.0, 0.9, 1.5, 0.7}},
        {4, 2, 5, {5, 1, 3, 2}, {1.0, 1.1, 0.95, 1.3, 0.8}},
        {5, 3, 3, {8, 2, 5, 7, 1}, {0.5, 1.0, 1.5}},
        {6, 2, 4, {9, 3, 6, 2, 4, 5}, {1.0, 1.05, 0.9, 1.2}},
        {7, 3, 2, {1, 2, 3, 4, 5, 6, 7}, {0.8, 1.3}},
        {8, 4, 6, {4, 8, 1, 2, 7, 3, 6, 5}, {1.0, 0.95, 1.1, 0.85, 1.2, 0.9}},
        {5, 5, 7, {10, 9, 8, 7, 6}, {1.0, 0.9, 0.8, 0.7, 1.1, 1.2, 1.3}},
        {3, 2, 5, {1, 10, 100}, {2.0, 1.0, 0.5, 1.5, 0.1}}
    };

    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& tc : tests) {
            double ans = sol.minTime(tc.n, tc.k, tc.m, tc.time, tc.mul);
            DoNotOptimize(ans);
            //checksum += static_cast<int>(ans);
        }
        //sink = checksum;
    }
    return 0;
}