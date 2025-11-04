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
#include <chrono>

using namespace std;

class Solution {
public:
    int maxLen(int n, vector<vector<int>>& edges, string label) {
        auto popcount = [](int x) -> int {
            return __builtin_popcount(x);
        };

        long long totalEdges = (static_cast<long long>(n) * (n - 1)) / 2;
        if (static_cast<long long>(edges.size()) == totalEdges) {
            vector<int> cnt(26, 0);
            for (char c : label) {
                cnt[c - 'a']++;
            }
            int pairs = 0;
            bool hasOdd = false;
            for (int c : cnt) {
                pairs += (c / 2) * 2;
                if (c % 2) hasOdd = true;
            }
            return pairs + (hasOdd ? 1 : 0);
        }

        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        int m = 1 << n;
        vector<vector<vector<char>>> dp(m, vector<vector<char>>(n, vector<char>(n, 0)));
        for (int u = 0; u < n; ++u) {
            dp[1 << u][u][u] = 1;
        }
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            if (label[u] == label[v]) {
                int a = min(u, v), b = max(u, v);
                dp[(1 << u) | (1 << v)][a][b] = 1;
            }
        }

        int result = 0;
        for (int mask = 1; mask < m; ++mask) {
            for (int u = 0; u < n; ++u) {
                for (int v = u; v < n; ++v) {
                    if (!dp[mask][u][v]) continue;
                    result = max(result, popcount(mask));
                    for (int nu : adj[u]) {
                        if (mask & (1 << nu)) continue;
                        for (int nv : adj[v]) {
                            if (mask & (1 << nv)) continue;
                            if (nu == nv) continue;
                            if (label[nu] == label[nv]) {
                                int a = min(nu, nv), b = max(nu, nv);
                                dp[mask | (1 << nu) | (1 << nv)][a][b] = 1;
                            }
                        }
                    }
                }
            }
        }
        return result;
    }
};

struct TestCase {
    int n;
    vector<vector<int>> edges;
    string label;
};

static vector<vector<int>> build_complete_edges(int n) {
    vector<vector<int>> e;
    e.reserve((long long)n * (n - 1) / 2);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            e.push_back({i, j});
        }
    }
    return e;
}

static vector<vector<int>> build_almost_complete_edges(int n, int skip_u, int skip_v) {
    vector<vector<int>> e;
    e.reserve((long long)n * (n - 1) / 2 - 1);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if ((i == skip_u && j == skip_v) || (i == skip_v && j == skip_u)) continue;
            e.push_back({i, j});
        }
    }
    return e;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Single node
    tests.push_back({
        1,
        {},
        "a"
    });

    // 2) Two nodes, connected, same label
    tests.push_back({
        2,
        {{0,1}},
        "aa"
    });

    // 3) Two nodes, disconnected, different labels
    tests.push_back({
        2,
        {},
        "ab"
    });

    // 4) Three-node path with palindromic labels
    tests.push_back({
        3,
        {{0,1},{1,2}},
        "aba"
    });

    // 5) Four-node cycle
    tests.push_back({
        4,
        {{0,1},{1,2},{2,3},{3,0}},
        "abca"
    });

    // 6) Five-node star centered at 0
    tests.push_back({
        5,
        {{0,1},{0,2},{0,3},{0,4}},
        "abcba"
    });

    // 7) Six-node almost complete graph (skip edge 0-5)
    tests.push_back({
        6,
        build_almost_complete_edges(6, 0, 5),
        "abccba"
    });

    // 8) Seven-node sparse tree-like structure
    tests.push_back({
        7,
        {{0,1},{0,2},{1,3},{2,4},{4,5},{5,6}},
        "abacaba"
    });

    // 9) Eight-node disconnected components (path + cycle)
    tests.push_back({
        8,
        {{0,1},{1,2},{2,3}, {4,5},{5,6},{6,7},{7,4}},
        "abcdabcd"
    });

    // 10) Twenty-node complete graph to hit the fast path
    {
        int n = 20;
        vector<vector<int>> edges = build_complete_edges(n);
        string label = "abcdefghijklmnopqrst"; // 20 unique letters
        tests.push_back({n, edges, label});
    }

    Solution sol;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    long long total = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        TestCase& tc = tests[iter % tests.size()];
        total += sol.maxLen(tc.n, tc.edges, tc.label);
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Total result: " << total << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}