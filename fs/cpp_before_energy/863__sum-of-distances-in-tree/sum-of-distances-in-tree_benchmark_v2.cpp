#include <iostream>
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

#include <vector>
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

struct TestCase {
    int N;
    vector<vector<int>> edges;
};

int main() {
    vector<TestCase> tests = {
        {2, {{0,1}}},
        {3, {{0,1},{1,2}}},
        {4, {{0,1},{0,2},{0,3}}},
        {5, {{0,1},{1,2},{2,3},{3,4}}},
        {6, {{0,1},{0,2},{1,3},{1,4},{2,5}}},
        {7, {{3,0},{3,1},{3,2},{3,4},{3,5},{3,6}}},
        {8, {{0,1},{1,2},{1,3},{2,4},{2,5},{3,6},{6,7}}},
        {9, {{0,1},{0,2},{2,3},{2,4},{4,5},{5,6},{6,7},{6,8}}},
        {10, {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{5,8},{5,9}}},
        {12, {{0,1},{0,2},{0,3},{1,4},{1,5},{2,6},{2,7},{3,8},{8,9},{9,10},{10,11}}}
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (auto& tc : tests) {
            vector<int> res = sol.sumOfDistancesInTree(tc.N, tc.edges);
            DoNotOptimize(res);
            // for (int v : res) {
            //     checksum += v;
            // }
        }
        //sink = checksum;
    }

    return 0;
}