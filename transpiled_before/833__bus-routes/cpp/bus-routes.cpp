#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

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