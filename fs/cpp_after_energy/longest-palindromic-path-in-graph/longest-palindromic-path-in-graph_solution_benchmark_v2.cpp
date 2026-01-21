#include <vector>
#include <string>
#include <algorithm>

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
    vector<TestCase> tests;
    tests.reserve(10);

    // 1) n=1, complete
    tests.push_back({1, build_complete_edges(1), string("a")});

    // 2) n=5, complete
    tests.push_back({5, build_complete_edges(5), string("abcde")});

    // 3) n=6, complete
    tests.push_back({6, build_complete_edges(6), string("aabbcc")});

    // 4) n=12, complete
    tests.push_back({12, build_complete_edges(12), string("abacabadabac")});

    // 5) n=7, almost complete (missing one edge)
    tests.push_back({7, build_almost_complete_edges(7, 1, 5), string("abacaba")});

    // 6) n=9, path
    {
        vector<vector<int>> e;
        for (int i = 0; i < 8; ++i) e.push_back({i, i + 1});
        tests.push_back({9, e, string("abccbaabc")});
    }

    // 7) n=9, star centered at 0
    {
        vector<vector<int>> e;
        for (int i = 1; i < 9; ++i) e.push_back({0, i});
        tests.push_back({9, e, string("aaaaaaaaa")});
    }

    // 8) n=7, cycle
    {
        vector<vector<int>> e;
        for (int i = 0; i < 6; ++i) e.push_back({i, i + 1});
        e.push_back({6, 0});
        tests.push_back({7, e, string("abcdefa")});
    }

    // 9) n=10, tree
    {
        vector<vector<int>> e = {
            {0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{4,8},{6,9}
        };
        tests.push_back({10, e, string("abcabcabca")});
    }

    // 10) n=8, two components (two paths)
    {
        vector<vector<int>> e = {
            {0,1},{1,2},{2,3},
            {4,5},{5,6},{6,7}
        };
        tests.push_back({8, e, string("abbaabba")});
    }

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            int res = sol.maxLen(t.n, const_cast<vector<vector<int>>&>(t.edges), t.label);
            DoNotOptimize(res); 
            //checksum += res;
        }
        //sink = checksum;
    }

    return 0;
}