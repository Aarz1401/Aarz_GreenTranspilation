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