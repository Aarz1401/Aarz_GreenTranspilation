#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std;

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int S, int T) {
        if (S == T) return 0;

        unordered_map<int, unordered_set<int>> to_route;
        for (int i = 0; i < static_cast<int>(routes.size()); ++i) {
            for (int stop : routes[i]) {
                to_route[stop].insert(i);
            }
        }

        int result = 1;
        vector<int> q{S};
        unordered_set<int> lookup;
        lookup.insert(S);

        while (!q.empty()) {
            vector<int> next_q;
            for (int stop : q) {
                auto itRoutesAtStop = to_route.find(stop);
                if (itRoutesAtStop == to_route.end()) continue;
                // Iterate over a copy to avoid issues if underlying sets change elsewhere
                vector<int> route_indices(itRoutesAtStop->second.begin(), itRoutesAtStop->second.end());
                for (int i : route_indices) {
                    for (int next_stop : routes[i]) {
                        if (lookup.count(next_stop)) continue;
                        if (next_stop == T) return result;
                        next_q.push_back(next_stop);
                        auto it2 = to_route.find(next_stop);
                        if (it2 != to_route.end()) {
                            it2->second.erase(i);
                        }
                        lookup.insert(next_stop);
                    }
                }
            }
            q.swap(next_q);
            ++result;
        }

        return -1;
    }
};

int main() {
    // Prepare 10 diverse test cases
    vector<vector<vector<int>>> allRoutes;
    vector<pair<int, int>> ST;

    // Test 1: Basic example - expect 2
    allRoutes.push_back({{1, 2, 7}, {3, 6, 7}});
    ST.emplace_back(1, 6);

    // Test 2: S == T - expect 0
    allRoutes.push_back({{1, 5, 9}});
    ST.emplace_back(5, 5);

    // Test 3: Unreachable target - expect -1
    allRoutes.push_back({{1, 2, 3}, {4, 5, 6}});
    ST.emplace_back(1, 6);

    // Test 4: Direct bus available - expect 1
    allRoutes.push_back({{10, 20, 30}, {5, 15}});
    ST.emplace_back(20, 30);

    // Test 5: Multiple transfers needed - expect 4
    allRoutes.push_back({{1, 5, 9}, {9, 10}, {10, 15}, {15, 20}});
    ST.emplace_back(1, 20);

    // Test 6: Large stop IDs - expect 4
    allRoutes.push_back({{1000000, 2000000}, {2000000, 3000000}, {3000000, 4000000, 5000000}, {5000000, 6000000}, {7000000}});
    ST.emplace_back(1000000, 6000000);

    // Test 7: Branching paths - expect minimal transfers (likely 4)
    allRoutes.push_back({{1, 2, 3, 4}, {4, 5, 6}, {2, 7}, {7, 8, 9}, {9, 10}});
    ST.emplace_back(1, 10);

    // Test 8: Single large route - expect 1
    {
        vector<int> bigRoute;
        for (int i = 0; i < 200; ++i) bigRoute.push_back(i);
        allRoutes.push_back({bigRoute});
        ST.emplace_back(0, 199);
    }

    // Test 9: No routes - expect -1
    allRoutes.push_back({});
    ST.emplace_back(1, 2);

    // Test 10: Overlapping routes with immediate reach - likely 1
    allRoutes.push_back({{1, 1, 1, 2}, {2, 3, 3, 4}, {4, 5}, {1, 6}, {6, 7, 8, 9, 10}});
    ST.emplace_back(1, 10);

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < allRoutes.size(); ++i) {
            // Make a copy of routes for each call to avoid any accidental state across runs
            vector<vector<int>> routes = allRoutes[i];
            int S = ST[i].first;
            int T = ST[i].second;
            int res = sol.numBusesToDestination(routes, S, T);
            checksum += res;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}