#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <utility>
#include <algorithm>
#include <functional>
#include <cstdint>
using namespace std;

// Time:  O((|E| + |V|) * log|V|) = O(|E| * log|V|)
// Space: O(|E| + |V|)

class Solution {
public:
    int reachableNodes(vector<vector<int>>& edges, int M, int N) {
        vector<vector<pair<int, int>>> adj(N);
        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
        }

        using PLL = pair<long long, int>;
        priority_queue<PLL, vector<PLL>, greater<PLL>> min_heap;
        const long long INF = numeric_limits<long long>::max() / 4;

        vector<long long> best(N, INF);
        vector<unordered_map<int, int>> count(N);

        best[0] = 0;
        min_heap.emplace(0LL, 0);

        long long result = 0;
        while (!min_heap.empty()) {
            auto [curr_total, u] = min_heap.top();
            min_heap.pop();
            if (curr_total != best[u]) {
                continue;
            }
            if (curr_total > M) {
                continue;
            }
            result += 1;
            for (const auto& p : adj[u]) {
                int v = p.first;
                int w = p.second;
                long long remain = M - curr_total;
                int take = static_cast<int>(min<long long>(w, max<long long>(0, remain)));
                count[u][v] = take;
                long long next_total = curr_total + w + 1;
                if (next_total <= M && next_total < best[v]) {
                    best[v] = next_total;
                    min_heap.emplace(next_total, v);
                }
            }
        }

        for (const auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            long long a = 0, b = 0;
            auto it = count[u].find(v);
            if (it != count[u].end()) a = it->second;
            auto jt = count[v].find(u);
            if (jt != count[v].end()) b = jt->second;
            result += min<long long>(w, a + b);
        }

        return static_cast<int>(result);
    }
};

struct TestCase {
    vector<vector<int>> edges;
    int M;
    int N;
};

int main() {
    vector<TestCase> tests = {
        { { {0,1,10}, {0,2,1}, {1,2,2} }, 6, 3 },
        { { {0,1,4}, {1,2,3}, {2,3,2}, {3,4,1} }, 0, 5 },
        { { {0,1,2}, {1,2,2}, {2,3,2}, {3,4,2}, {4,5,2} }, 5, 6 },
        { { {0,1,3}, {0,2,4}, {0,3,5}, {0,4,1}, {0,5,2} }, 7, 6 },
        { { {0,1,1000000000}, {1,2,1000000000}, {0,2,1000000000} }, 1000000000, 3 },
        { { {0,1,1}, {2,3,5}, {3,4,5}, {5,6,5} }, 2, 7 },
        { { {0,1,1}, {1,2,1}, {2,3,1}, {3,4,1}, {4,0,1} }, 3, 5 },
        { { {0,1,2}, {0,2,3}, {0,3,4}, {1,2,5}, {1,3,6}, {2,3,7} }, 8, 4 },
        { { {0,1,1}, {1,2,4}, {2,3,6}, {3,4,8}, {4,5,10}, {5,6,12}, {6,7,14}, {0,7,20}, {2,6,7} }, 15, 8 },
        { { {0,1,3}, {1,2,3}, {2,3,3}, {3,4,3}, {0,4,10} }, 9, 5 }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& t : tests) {
            int r = sol.reachableNodes(t.edges, t.M, t.N);
            DoNotOptimize(r);
        }
        //sink = checksum;
    }
    return 0;
}