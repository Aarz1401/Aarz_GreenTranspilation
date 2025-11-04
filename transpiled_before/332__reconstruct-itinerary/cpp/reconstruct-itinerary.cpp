#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
public:
    // Time:  O(|V| + |E|log|V|)
    // Space: O(|V| + |E|)
    // Hierholzer Algorithm
    std::vector<std::string> findItinerary(std::vector<std::vector<std::string>>& tickets) {
        std::unordered_map<std::string, std::vector<std::string>> adj;
        for (const auto& t : tickets) {
            adj[t[0]].push_back(t[1]);
        }
        for (auto& kv : adj) {
            std::sort(kv.second.rbegin(), kv.second.rend());  // reverse sort for efficient pop_back()
        }

        const std::string origin = "JFK";
        std::vector<std::string> result;
        std::vector<std::string> stk;
        stk.push_back(origin);

        // Iterative Hierholzer's algorithm
        while (!stk.empty()) {
            auto& dests = adj[stk.back()];
            if (!dests.empty()) {
                std::string next = std::move(dests.back());
                dests.pop_back();
                stk.push_back(std::move(next));
            } else {
                result.push_back(stk.back());
                stk.pop_back();
            }
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};