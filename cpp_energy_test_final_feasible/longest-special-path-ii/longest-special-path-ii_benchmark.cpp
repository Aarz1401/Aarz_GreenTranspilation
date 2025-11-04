#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <array>
#include <climits>
#include <chrono>
using namespace std;

int i = 0;

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
                const int iterations = 1000;
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Define 10 diverse test inputs
    vector<vector<vector<int>>> all_edges(10);
    vector<vector<int>> all_nums(10);

    // 1) Single node
    all_edges[0] = {};
    all_nums[0] = {1};

    // 2) Line of 3 nodes with increasing weights and nums
    all_edges[1] = {
        {0, 1, 2},
        {1, 2, 3}
    };
    all_nums[1] = {1, 2, 3};

    // 3) Star tree with duplicates in nums
    all_edges[2] = {
        {0, 1, 1},
        {0, 2, 2},
        {0, 3, 3},
        {0, 4, 4}
    };
    all_nums[2] = {1, 1, 2, 2, 3};

    // 4) Balanced binary tree
    all_edges[3] = {
        {0, 1, 3},
        {0, 2, 5},
        {1, 3, 2},
        {1, 4, 4},
        {2, 5, 6},
        {2, 6, 1}
    };
    all_nums[3] = {2, 3, 2, 1, 3, 1, 2};

    // 5) Random small tree
    all_edges[4] = {
        {0, 1, 7},
        {1, 2, 1},
        {1, 3, 8},
        {3, 4, 2},
        {2, 5, 9}
    };
    all_nums[4] = {5, 1, 5, 2, 3, 2};

    // 6) Zero weights line
    all_edges[5] = {
        {0, 1, 0},
        {1, 2, 0},
        {2, 3, 0}
    };
    all_nums[5] = {1, 2, 1, 2};

    // 7) Very large weights
    all_edges[6] = {
        {0, 1, 1000000000},
        {1, 2, 1000000000},
        {1, 3, 1000000000}
    };
    all_nums[6] = {10, 9, 8, 7};

    // 8) Chain of 10 nodes
    all_edges[7] = {
        {0, 1, 1},
        {1, 2, 2},
        {2, 3, 3},
        {3, 4, 4},
        {4, 5, 5},
        {5, 6, 6},
        {6, 7, 7},
        {7, 8, 8},
        {8, 9, 9}
    };
    all_nums[7] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2};

    // 9) All nums identical
    all_edges[8] = {
        {0, 1, 3},
        {1, 2, 3},
        {2, 3, 3},
        {3, 4, 3}
    };
    all_nums[8] = {7, 7, 7, 7, 7};

    // 10) Negative and zero nums in a star
    all_edges[9] = {
        {0, 1, 2},
        {0, 2, 2},
        {0, 3, 2},
        {0, 4, 2},
        {0, 5, 2}
    };
    all_nums[9] = {0, -1, -1, 0, -5, 0};

    Solution sol;

    long long checksum = 0;

    const int iterations = 1000;
    auto start = chrono::high_resolution_clock::now();
    for (int iter = 0; iter < iterations; ++iter) {
        for (int t = 0; t < 10; ++t) {
            vector<vector<int>>& edgesRef = all_edges[t];
            vector<int>& numsRef = all_nums[t];
            vector<int> res = sol.longestSpecialPath(edgesRef, numsRef);
            checksum += res[0] * 1000003LL + res[1];
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Time (microseconds): " << duration << "\n";

    return 0;
}