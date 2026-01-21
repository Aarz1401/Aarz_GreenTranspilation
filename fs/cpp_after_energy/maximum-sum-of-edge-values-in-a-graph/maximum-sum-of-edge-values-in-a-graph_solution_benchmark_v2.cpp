#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    long long maxScore(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(n, false);
        auto bfs = [&](int start) {
            vector<int> comp;
            queue<int> q;
            visited[start] = true;
            q.push(start);
            while (!q.empty()) {
                int u = q.front(); q.pop();
                comp.push_back(u);
                for (int v : adj[u]) {
                    if (visited[v]) continue;
                    visited[v] = true;
                    q.push(v);
                }
            }
            return comp;
        };

        auto f = [&](long long l, long long r, bool is_cycle) -> long long {
            long long a = r, b = r;
            long long result = 0;
            for (long long c = r - 1; c >= l; --c) {
                result += a * c;
                long long na = b, nb = c;
                a = na, b = nb;
            }
            if (is_cycle) {
                result += a * b;
            }
            return result;
        };

        vector<int> cycles, chains;
        for (int u = 0; u < n; ++u) {
            if (visited[u]) continue;
            vector<int> comp = bfs(u);
            bool is_cycle = true;
            for (int x : comp) {
                if (adj[x].size() != 2) { is_cycle = false; break; }
            }
            if (is_cycle) {
                cycles.push_back((int)comp.size());
            } else {
                chains.push_back((int)comp.size());
            }
        }

        long long result = 0;
        int cur = n;
        for (int l : cycles) {
            result += f(cur - l + 1, cur, true);
            cur -= l;
        }

        size_t max_len = 0;
        for (int l : chains) max_len = max(max_len, (size_t)l);
        vector<int> cnt(max_len + 1, 0);
        for (int l : chains) cnt[l]++;

        for (int l = (int)cnt.size() - 1; l >= 0; --l) {
            for (int k = 0; k < cnt[l]; ++k) {
                result += f(cur - l + 1, cur, false);
                cur -= l;
            }
        }
        return result;
    }
};

struct Test {
    int n;
    vector<vector<int>> edges;
};

int main() {
    vector<Test> tests = {
        // 1) Single node, no edges
        {1, {}},
        // 2) Two nodes, one edge (path)
        {2, {{0,1}}},
        // 3) Triangle cycle
        {3, {{0,1},{1,2},{2,0}}},
        // 4) Square cycle
        {4, {{0,1},{1,2},{2,3},{3,0}}},
        // 5) Path of 4 nodes
        {4, {{0,1},{1,2},{2,3}}},
        // 6) Star with 5 nodes (center 0)
        {5, {{0,1},{0,2},{0,3},{0,4}}},
        // 7) Triangle + isolated node
        {4, {{0,1},{1,2},{2,0}}},
        // 8) 4-cycle + 3-node path
        {7, {{0,1},{1,2},{2,3},{3,0},{4,5},{5,6}}},
        // 9) Two disjoint edges + isolated node
        {5, {{0,1},{3,4}}},
        // 10) 5-cycle + small tree
        {10, {{0,1},{1,2},{2,3},{3,4},{4,0},{5,6},{6,7},{6,8},{8,9}}}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (int i = 0; i < (int)tests.size(); ++i) {
            long long r = sol.maxScore(tests[i].n, tests[i].edges);
            DoNotOptimize(r); 
            //checksum ^= static_cast<int>(r ^ (r >> 32));
        }
        //sink = checksum;
    }

    return 0;
}