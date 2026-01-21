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
#include <cstdint>
#include <chrono>
using namespace std;

class Solution {
public:
    vector<bool> findAnswer(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> adj(n);
        for (int v = 1; v < n; ++v) {
            adj[parent[v]].push_back(v);
        }

        // Iterative DFS to build postorder string 'curr' and lookup intervals [left, right]
        int cnt = 0;
        vector<char> curr;
        curr.reserve(n);
        vector<pair<int, int>> lookup(n, {-1, -1});

        struct Frame {
            int step;
            int u;
            int left;
        };
        vector<Frame> stk;
        stk.push_back({1, 0, 0});
        while (!stk.empty()) {
            Frame f = stk.back();
            stk.pop_back();
            if (f.step == 1) {
                int u = f.u;
                stk.push_back({2, u, cnt});
                // push children in reverse to process in original order
                for (int i = (int)adj[u].size() - 1; i >= 0; --i) {
                    stk.push_back({1, adj[u][i], 0});
                }
            } else { // step 2
                int u = f.u;
                int left = f.left;
                curr.push_back(s[u]);
                lookup[u] = {left, cnt};
                ++cnt;
            }
        }

        // Manacher's algorithm on curr
        auto manacher = [](const vector<char>& arr) -> vector<int> {
            string T;
            T.reserve(2 * arr.size() + 3);
            T.push_back('^');
            T.push_back('#');
            for (char c : arr) {
                T.push_back(c);
                T.push_back('#');
            }
            T.push_back('$');

            int m = T.size();
            vector<int> P(m, 0);
            int C = 0, R = 0;
            for (int i = 1; i < m - 1; ++i) {
                int i_mirror = 2 * C - i;
                if (R > i) {
                    P[i] = min(R - i, P[i_mirror]);
                }
                while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                    ++P[i];
                }
                if (i + P[i] > R) {
                    C = i;
                    R = i + P[i];
                }
            }
            return P;
        };

        vector<int> P = manacher(curr);

        vector<bool> ans(n, false);
        for (int u = 0; u < n; ++u) {
            int left = lookup[u].first;
            int right = lookup[u].second;
            int center = (2 * (left + 1) + 2 * (right + 1)) / 2;
            ans[u] = (P[center] >= right - left + 1);
        }
        return ans;
    }
};
