#include <iostream>
#include <algorithm>
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

volatile int sink = 0;

int main() {
    std::vector<std::vector<std::vector<std::string>>> tests = {
        { {"MUC","LHR"}, {"JFK","MUC"}, {"SFO","SJC"}, {"LHR","SFO"} },
        { {"JFK","KUL"}, {"JFK","NRT"}, {"NRT","JFK"} },
        { {"JFK","AAA"}, {"JFK","AAA"}, {"AAA","JFK"} },
        { {"JFK","ATL"}, {"ATL","SFO"}, {"SFO","JFK"} },
        { {"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"} },
        { {"JFK","AAA"}, {"JFK","BBB"}, {"AAA","CCC"}, {"CCC","JFK"}, {"BBB","DDD"}, {"DDD","EEE"} },
        { {"JFK","AAB"}, {"JFK","AAA"}, {"AAA","JFK"}, {"AAB","AAA"} },
        { {"JFK","LAX"}, {"JFK","LAX"}, {"LAX","JFK"}, {"LAX","SFO"}, {"SFO","LAX"} },
        { {"JFK","AAA"}, {"AAA","BBB"}, {"BBB","AAA"}, {"AAA","JFK"}, {"JFK","CCC"}, {"CCC","DDD"}, {"DDD","JFK"}, {"CCC","EEE"}, {"EEE","CCC"} },
        { {"JFK","MUC"}, {"JFK","LHR"}, {"LHR","MUC"}, {"MUC","SFO"}, {"SFO","ATL"}, {"ATL","JFK"} }
    };

    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tickets : tests) {
            std::vector<std::string> res = sol.findItinerary(tickets);
            checksum += static_cast<int>(res.size());
            if (!res.empty()) {
                checksum += static_cast<int>(static_cast<unsigned char>(res.front()[0]));
                checksum += static_cast<int>(static_cast<unsigned char>(res.back()[0]));
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}