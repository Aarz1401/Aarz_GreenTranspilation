#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
#include <utility>
#include <algorithm>
#include <numeric>

using namespace std;

// Time:  O(n)
// Space: O(n)

class Solution {
public:
    vector<int> sumOfDistancesInTree(int N, vector<vector<int>>& edges) {
        vector<vector<int>> graph(N);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<int> count(N, 1);
        vector<int> result(N, 0);

        dfs(graph, 0, -1, count, result);
        dfs2(graph, 0, -1, count, result);
        return result;
    }

private:
    void dfs(const vector<vector<int>>& graph, int node, int parent, vector<int>& count, vector<int>& result) {
        for (int nei : graph[node]) {
            if (nei != parent) {
                dfs(graph, nei, node, count, result);
                count[node] += count[nei];
                result[node] += result[nei] + count[nei];
            }
        }
    }

    void dfs2(const vector<vector<int>>& graph, int node, int parent, vector<int>& count, vector<int>& result) {
        int n = static_cast<int>(count.size());
        for (int nei : graph[node]) {
            if (nei != parent) {
                result[nei] = result[node] - count[nei] + (n - count[nei]);
                dfs2(graph, nei, node, count, result);
            }
        }
    }
};