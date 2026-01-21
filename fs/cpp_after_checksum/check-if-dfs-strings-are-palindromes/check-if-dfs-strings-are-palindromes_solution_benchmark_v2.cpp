#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
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

struct TestCase {
    vector<int> parent;
    string s;
};

volatile int sink = 0;

int main() {
    vector<TestCase> tests = {
        { {-1}, "z" },
        { {-1, 0, 1, 2, 3}, "abcba" },
        { {-1, 0, 0, 0, 0, 0}, "abccba" },
        { {-1, 0, 0, 1, 1, 2, 2}, "abacaba" },
        { {-1, 0, 0, 1, 1, 3, 3, 2}, "abcdedcb" },
        { {-1, 0, 1, 2, 3, 4, 5, 6, 7, 8}, "aaaaabaaaa" },
        { {-1, 0, 0, 0, 1, 1, 2, 3, 3, 6, 8, 8}, "abcddcbaabca" },
        { {-1, 0, 0, 0, 1, 3, 3, 6, 6}, "racecarzz" },
        { {-1, 0}, "ab" },
        { {-1, 0, 0, 1, 3, 3, 2, 2, 2, 8, 8}, "zzxyxxyxxzz" }
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            vector<bool> ans = sol.findAnswer(const_cast<vector<int>&>(tc.parent), tc.s);
            for (bool b : ans) checksum += b;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}