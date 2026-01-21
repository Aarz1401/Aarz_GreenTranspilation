#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <limits>
#include <chrono>
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
    // Define 10 diverse test inputs
    vector<TestCase> tests;
    tests.reserve(10);

    tests.push_back(TestCase{1, 1, {}}); // 0 stops
    tests.push_back(TestCase{100, 1, {{10, 100}}}); // impossible
    tests.push_back(TestCase{100, 10, {{10, 60}, {20, 30}, {30, 30}, {60, 40}}}); // typical => 2
    tests.push_back(TestCase{100, 50, {{25, 25}, {50, 25}}}); // needs 2
    tests.push_back(TestCase{1000, 299, {{100, 100}, {200, 100}, {300, 100}, {400, 100}}}); // impossible
    tests.push_back(TestCase{100, 100, {{10, 10}, {20, 20}}}); // already enough fuel
    tests.push_back(TestCase{100, 25, {{25, 25}, {25, 25}, {50, 25}, {75, 25}}}); // duplicate positions
    tests.push_back(TestCase{5000, 500, {{400, 300}, {800, 300}, {1200, 300}, {1600, 300}, {2000, 300}, {2400, 300}, {2800, 300}, {3200, 300}, {3600, 300}, {4000, 300}, {4400, 300}, {4800, 300}}}); // many mid-size stops
    tests.push_back(TestCase{300, 50, {{25, 0}, {50, 0}, {60, 90}, {120, 0}, {180, 30}, {240, 100}}}); // includes zero-capacity stations
    tests.push_back(TestCase{1000000, 100000, {{100000, 100000}, {200000, 100000}, {300000, 100000}, {400000, 100000}, {500000, 100000}, {600000, 100000}, {700000, 100000}, {800000, 100000}, {900000, 100000}}}); // large numbers

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            // Use the stored stations directly; Solution does not modify them
            int result = sol.minRefuelStops(tests[i].target, tests[i].startFuel, tests[i].stations);
            checksum += static_cast<long long>(result) * static_cast<long long>((i + 1) + (iter % 7));
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}