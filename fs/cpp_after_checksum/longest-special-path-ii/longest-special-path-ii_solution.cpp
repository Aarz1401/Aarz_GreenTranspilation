#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <string>
#include <climits>
#include <cmath>
#include <utility>
#include <array>
#include <chrono>
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

        struct Frame {
            int step;           // 1: enter node, 2: iterate children, 3: pop prefix, 4: exit node (restore)
            int u, p, d;        // node, parent, depth
            int i;              // child index iterator
            int prev_d;         // previous depth for value
            array<int, 2> left; // top-2 depths tracker
        };

        unordered_map<int, int> lookup; // default -1 behavior
        vector<long long> prefix(1, 0); // prefix[depth] = total length to this depth
        pair<long long, long long> result = {LLONG_MAX, LLONG_MAX};

        vector<Frame> stk;
        stk.push_back(Frame{1, 0, -1, 0, 0, -1, {-1, -1}});

        while (!stk.empty()) {
            Frame f = stk.back(); stk.pop_back();
            if (f.step == 1) {
                int u = f.u, p = f.p, d = f.d;
                array<int, 2> left = f.left;

                int key = nums[u] - 1;
                int prev_d = -1;
                auto it = lookup.find(key);
                if (it != lookup.end()) prev_d = it->second;
                lookup[key] = d;

                array<int, 2> new_left = left;
                int curr = prev_d;
                const int iterations = 1;
                for (int iter = 0; iter < iterations; ++iter) {
                    if (curr > new_left[i]) {
                        int tmp = new_left[i];
                        new_left[i] = curr;
                        curr = tmp;
                    }
                }

                long long len = prefix[d] - prefix[new_left[1] + 1];
                pair<long long, long long> cand = {-len, (long long)(d - new_left[1])};
                if (cand < result) result = cand;

                stk.push_back(Frame{4, u, 0, 0, 0, prev_d, {0, 0}});
                stk.push_back(Frame{2, u, p, d, 0, 0, new_left});
            } else if (f.step == 2) {
                int u = f.u, p = f.p, d = f.d, i = f.i;
                array<int, 2> left = f.left;

                if (i == (int)adj[u].size()) {
                    continue;
                }
                stk.push_back(Frame{2, u, p, d, i + 1, 0, left});

                int v = adj[u][i].first;
                int l = adj[u][i].second;
                if (v == p) {
                    continue;
                }
                prefix.push_back(prefix.back() + l);
                stk.push_back(Frame{3, 0, 0, 0, 0, 0, {0, 0}});
                stk.push_back(Frame{1, v, u, d + 1, 0, 0, left});
            } else if (f.step == 3) {
                if (!prefix.empty()) prefix.pop_back();
            } else if (f.step == 4) {
                int u = f.u, prev_d = f.prev_d;
                int key = nums[u] - 1;
                lookup[key] = prev_d;
            }
        }

        return vector<int>{(int)(-result.first), (int)(result.second)};
    }
};
