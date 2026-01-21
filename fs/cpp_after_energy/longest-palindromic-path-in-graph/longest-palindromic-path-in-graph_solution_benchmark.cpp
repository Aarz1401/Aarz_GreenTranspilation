
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
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

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

    // 1) n=1, complete (trivial)
    tests.push_back(TestCase{
        1,
        build_complete_edges(1),
        "a"
    });

    // 2) n=2, complete
    tests.push_back(TestCase{
        2,
        build_complete_edges(2),
        "aa"
    });

    // 3) n=3, complete
    tests.push_back(TestCase{
        3,
        build_complete_edges(3),
        "abc"
    });

    // 4) n=4, path graph
    {
        vector<vector<int>> e = {{0,1},{1,2},{2,3}};
        tests.push_back(TestCase{
            4,
            e,
            "abba"
        });
    }

    // 5) n=6, star graph
    {
        int n = 6;
        vector<vector<int>> e;
        for (int i = 1; i < n; ++i) e.push_back({0, i});
        tests.push_back(TestCase{
            n,
            e,
            "abccba"
        });
    }

    // 6) n=8, complete
    tests.push_back(TestCase{
        8,
        build_complete_edges(8),
        "aabbccdd"
    });

    // 7) n=9, complete
    tests.push_back(TestCase{
        9,
        build_complete_edges(9),
        "aaabbbccc"
    });

    // 8) n=10, almost complete (missing one edge)
    tests.push_back(TestCase{
        10,
        build_almost_complete_edges(10, 2, 7),
        "abcabcabca"
    });

    // 9) n=12, complete
    tests.push_back(TestCase{
        12,
        build_complete_edges(12),
        "aaaabbbbcccc"
    });

    // 10) n=14, complete
    tests.push_back(TestCase{
        14,
        build_complete_edges(14),
        "aabbccddeeffgg"
    });

    Solution sol;
    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.maxLen(tc.n, tc.edges, tc.label);
        }
    }

    auto end = high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed_ms = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms.count() << "\n";

    return 0;
}
