#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>
#include <chrono>
#include <utility>
#include <functional>

using namespace std;

class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], l = e[2];
            adj[u].emplace_back(v, l);
            adj[v].emplace_back(u, l);
        }

        unordered_map<int, int> lookup;  // key: nums[u]-1 -> last depth
        vector<long long> prefix(1, 0);  // prefix[depth]
        pair<long long, int> res = {LLONG_MAX / 4, INT_MAX / 4};

        function<void(int, int, int, int)> dfs = [&](int u, int p, int d, int left) {
            int key = nums[u] - 1;
            int prev_d = -1;
            auto it = lookup.find(key);
            if (it != lookup.end()) prev_d = it->second;
            lookup[key] = d;

            left = max(left, prev_d);
            long long cur_len = prefix[d] - prefix[left + 1];
            pair<long long, int> cand = { -cur_len, d - left };
            if (cand < res) res = cand;

            for (const auto& [v, w] : adj[u]) {
                if (v == p) continue;
                prefix.push_back(prefix.back() + w);
                dfs(v, u, d + 1, left);
                prefix.pop_back();
            }

            if (prev_d == -1) lookup.erase(key);
            else lookup[key] = prev_d;
        };

        if (n > 0) {
            dfs(0, -1, 0, -1);
        }

        return { static_cast<int>(-res.first), res.second };
    }
};

int main() {
    // Define 10 diverse test cases (each a tree to avoid cycles)
    vector<vector<vector<int>>> edgesList;
    vector<vector<int>> numsList;

    // 1. Single node
    edgesList.push_back({});
    numsList.push_back({1});

    // 2. Two nodes
    edgesList.push_back({{0, 1, 5}});
    numsList.push_back({1, 2});

    // 3. Chain of 5 nodes with increasing weights
    edgesList.push_back({{0,1,1},{1,2,2},{2,3,3},{3,4,4}});
    numsList.push_back({1,2,3,4,5});

    // 4. Star with 6 nodes, all nums equal
    edgesList.push_back({{0,1,1},{0,2,2},{0,3,3},{0,4,4},{0,5,5}});
    numsList.push_back({2,2,2,2,2,2});

    // 5. Balanced tree of 7 nodes with mixed nums
    edgesList.push_back({{0,1,3},{0,2,1},{1,3,4},{1,4,2},{2,5,7},{2,6,6}});
    numsList.push_back({3,1,2,3,2,1,3});

    // 6. Chain with zero weights
    edgesList.push_back({{0,1,0},{1,2,0},{2,3,0}});
    numsList.push_back({5,4,5,4});

    // 7. Larger tree of 10 nodes
    edgesList.push_back({{0,1,2},{1,2,5},{1,3,1},{3,4,3},{3,5,8},{2,6,1},{6,7,2},{6,8,4},{8,9,3}});
    numsList.push_back({1,3,2,3,1,2,4,4,3,5});

    // 8. Descending nums with big weights
    edgesList.push_back({{0,1,100},{1,2,200},{1,3,150},{3,4,250},{3,5,50},{2,6,300},{6,7,400}});
    numsList.push_back({8,7,6,5,4,3,2,1});

    // 9. Repeated pattern, mixed weights including zeros
    edgesList.push_back({{0,1,1},{1,2,2},{1,3,0},{3,4,5},{3,5,0},{2,6,7},{6,7,0},{6,8,9}});
    numsList.push_back({1,2,1,2,1,2,1,2,1});

    // 10. Deep chain of 12 nodes, alternating grouped nums
    edgesList.push_back({{0,1,1},{1,2,1},{2,3,1},{3,4,1},{4,5,1},{5,6,1},{6,7,1},{7,8,1},{8,9,1},{9,10,1},{10,11,1}});
    numsList.push_back({1,1,2,2,3,3,4,4,5,5,6,6});

    const int T = static_cast<int>(edgesList.size());
    Solution sol;

    volatile long long checksum = 0; // volatile to prevent aggressive optimization
    vector<int> lastResult;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int idx = iter % T;
        vector<vector<int>> edges = edgesList[idx];
        vector<int> nums = numsList[idx];
        vector<int> res = sol.longestSpecialPath(edges, nums);
        checksum += res[0] + 31LL * res[1] + idx;
        lastResult = res;
    }

    auto end = high_resolution_clock::now();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    // Print results to avoid optimization
    cout << "Checksum: " << checksum << "\n";
    if (!lastResult.empty()) {
        cout << "Last Result: [" << lastResult[0] << ", " << lastResult[1] << "]\n";
    } else {
        cout << "Last Result: []\n";
    }
    cout << "Total time (ns): " << duration_ns << "\n";

    return 0;
}