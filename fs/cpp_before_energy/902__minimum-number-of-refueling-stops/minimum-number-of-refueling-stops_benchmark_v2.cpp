#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <queue>
#include <utility>
#include <limits>
using namespace std;

// Time:  O(nlogn)
// Space: O(n)

class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        using ll = long long;

        vector<pair<ll, ll>> v;
        v.reserve(stations.size() + 1);
        for (const auto& st : stations) {
            v.emplace_back(static_cast<ll>(st[0]), static_cast<ll>(st[1]));
        }
        // Sentinel to process the final leg to target
        v.emplace_back(static_cast<ll>(target), numeric_limits<ll>::max());

        priority_queue<ll> max_heap;  // max-heap of capacities of reachable stations
        ll fuel = static_cast<ll>(startFuel);
        ll prev = 0;
        int result = 0;

        for (const auto& station : v) {
            ll location = station.first;
            ll capacity = station.second;

            fuel -= (location - prev);
            while (!max_heap.empty() && fuel < 0) {
                fuel += max_heap.top();
                max_heap.pop();
                ++result;
            }
            if (fuel < 0) {
                return -1;
            }
            max_heap.push(capacity);
            prev = location;
        }

        return result;
    }
};

struct TestCase {
    int target;
    int startFuel;
    vector<vector<int>> stations;
};

int main() {
    vector<TestCase> tests = {
        {100, 150, {{25, 10}}},
        {100, 50, {{25, 30}, {50, 25}, {75, 25}}},
        {100, 10, {{10, 60}, {20, 10}, {30, 10}, {60, 30}}},
        {100, 1, {{10, 100}}},
        {1000000000, 100000, {{100000, 100000}, {200000, 200000}, {400000, 300000}, {700000, 400000}, {1000000, 500000}, {2000000, 600000}, {5000000, 700000}, {10000000, 800000}, {50000000, 900000}, {100000000, 1000000}}},
        {100, 60, {{60, 40}}},
        {120, 25, {{10, 10}, {20, 10}, {30, 50}, {60, 30}, {90, 30}}},
        {500, 100, {{50, 50}, {100, 50}, {150, 50}, {200, 50}, {300, 100}, {400, 100}}},
        {200, 200, {{50, 30}, {150, 50}}},
        {300, 50, {{25, 25}, {50, 25}, {75, 25}, {100, 100}, {150, 50}, {200, 50}, {250, 50}}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& tc : tests) {
            int r = sol.minRefuelStops(tc.target, tc.startFuel, const_cast<vector<vector<int>>&>(tc.stations));
            DoNotOptimize(r);
        }
        //sink = checksum;
    }

    return 0;
}