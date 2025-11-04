#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minSwapsCouples(std::vector<int>& row) {
        int N = static_cast<int>(row.size()) / 2;
        std::vector<std::vector<int>> couples(N);
        for (int seat = 0; seat < static_cast<int>(row.size()); ++seat) {
            int num = row[seat];
            couples[num / 2].push_back(seat / 2);
        }
        std::vector<std::vector<int>> adj(N);
        for (const auto& c : couples) {
            int couch1 = c[0], couch2 = c[1];
            adj[couch1].push_back(couch2);
            adj[couch2].push_back(couch1);
        }

        auto removeEdge = [](std::vector<int>& vec, int val) {
            for (auto it = vec.begin(); it != vec.end(); ++it) {
                if (*it == val) {
                    vec.erase(it);
                    break;
                }
            }
        };

        int result = 0;
        for (int couch = 0; couch < N; ++couch) {
            if (adj[couch].empty()) continue;
            int couch1 = couch, couch2 = adj[couch].back();
            adj[couch].pop_back();
            while (couch2 != couch) {
                result += 1;
                removeEdge(adj[couch2], couch1);
                couch1 = couch2;
                couch2 = adj[couch2].back();
                adj[couch2].pop_back();
            }
        }
        return result;  // also equals to N - (# of cycles)
    }
};