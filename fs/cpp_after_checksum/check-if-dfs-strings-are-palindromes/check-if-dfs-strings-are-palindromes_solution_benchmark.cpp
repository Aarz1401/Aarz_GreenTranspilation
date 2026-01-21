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

static vector<int> generateParent(int n) {
    vector<int> p(n, -1);
    for (int v = 1; v < n; ++v) {
        p[v] = (int)((1LL * v * v + 3LL * v + 7) % v);
    }
    return p;
}

static string generateString(int n) {
    string s(n, 'a');
    for (int i = 0; i < n; ++i) {
        s[i] = char('a' + (int)((37LL * (i + 11) + 11LL * n) % 26));
    }
    return s;
}

int main() {
    // Define 10 diverse test inputs

    // 1) Single node
    vector<int> parent1 = {-1};
    string s1 = "a";

    // 2) Two-node chain
    vector<int> parent2 = {-1, 0};
    string s2 = "ab";

    // 3) Chain of 5
    vector<int> parent3 = {-1, 0, 1, 2, 3};
    string s3 = "abcde";

    // 4) Balanced binary tree with palindrome string
    vector<int> parent4 = {-1, 0, 0, 1, 1, 2, 2};
    string s4 = "racecar";

    // 5) Star tree of 10 nodes
    vector<int> parent5 = {-1, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    string s5 = "abcdefghij";

    // 6) Random-like tree n=50
    int n6 = 50;
    vector<int> parent6 = generateParent(n6);
    string s6 = generateString(n6);

    // 7) Random-like tree n=100
    int n7 = 100;
    vector<int> parent7 = generateParent(n7);
    string s7 = generateString(n7);

    // 8) Random-like tree n=300
    int n8 = 300;
    vector<int> parent8 = generateParent(n8);
    string s8 = generateString(n8);

    // 9) Random-like tree n=700
    int n9 = 700;
    vector<int> parent9 = generateParent(n9);
    string s9 = generateString(n9);

    // 10) Random-like tree n=1200
    int n10 = 1200;
    vector<int> parent10 = generateParent(n10);
    string s10 = generateString(n10);

    vector<vector<int>*> parents = {
        &parent1, &parent2, &parent3, &parent4, &parent5,
        &parent6, &parent7, &parent8, &parent9, &parent10
    };
    vector<string> strings = {s1, s2, s3, s4, s5, s6, s7, s8, s9, s10};

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < parents.size(); ++i) {
            vector<bool> res = sol.findAnswer(*parents[i], strings[i]);
            uint64_t local = 0;
            for (size_t j = 0; j < res.size(); ++j) {
                local += res[j] ? (j + 1) : 0;
            }
            // Mix in some per-test values to avoid trivial cancellation
            local ^= (uint64_t)res.size() * (i + 1);
            checksum += local;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed (ns): " << elapsed_ns << "\n";
    return 0;
}