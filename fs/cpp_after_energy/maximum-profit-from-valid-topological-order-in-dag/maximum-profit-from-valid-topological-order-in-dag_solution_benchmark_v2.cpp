#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    int maxProfit(int n, vector<vector<int>>& edges, vector<int>& score) {
        vector<int> adj(n, 0);
        for (const auto& e : edges) {
            int i = e[0], j = e[1];
            adj[j] |= (1 << i);
        }
        int total = 1 << n;
        const long long NEG = LLONG_MIN / 4;
        vector<long long> dp(total, NEG);
        dp[0] = 0;
        for (int mask = 0; mask < total; ++mask) {
            if (dp[mask] == NEG) continue;
            int l = __builtin_popcount((unsigned)mask) + 1;
            for (int i = 0; i < n; ++i) {
                if (mask & (1 << i)) continue;
                if ((mask & adj[i]) == adj[i]) {
                    int nmask = mask | (1 << i);
                    dp[nmask] = max(dp[nmask], dp[mask] + 1LL * l * score[i]);
                }
            }
        }
        return static_cast<int>(dp[total - 1]);
    }
};

struct TestCase {
    int n;
    vector<vector<int>> edges;
    vector<int> score;
};

int main() {
    vector<TestCase> tests = {
        {1, {}, {5}},
        {2, {{0,1}}, {3,4}},
        {3, {{0,1},{0,2}}, {2,-1,5}},
        {4, {{0,2},{1,3}}, {4,1,2,3}},
        {5, {{0,1},{1,2},{2,3},{3,4}}, {7,-3,4,-2,5}},
        {6, {}, {1,2,3,4,5,6}},
        {8, {{0,3},{0,4},{1,4},{1,5},{2,5},{3,6},{4,6},{5,7}}, {3,-5,2,8,7,-1,4,6}},
        {10, {{0,2},{1,2},{2,3},{2,4},{4,6},{3,5},{5,7},{6,8},{7,9}}, {5,-2,7,1,-3,4,9,-6,2,8}},
        {9, {{0,2},{0,3},{1,3},{1,4},{2,5},{3,5},{3,6},{4,6},{5,7},{6,8}}, {0,10,-4,3,-1,2,6,5,-2}},
        {11, {{0,3},{1,4},{2,5},{0,4},{1,5},{3,6},{4,6},{4,7},{5,7},{6,8},{7,9},{8,10},{9,10}}, {4,-3,5,2,-6,7,1,8,-2,3,6}}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (int t = 0; t < (int)tests.size(); ++t) {
            auto& tc = tests[t];
            int res = sol.maxProfit(tc.n, tc.edges, tc.score);
            DoNotOptimize(res);
            //checksum += res;
        }
        //sink = checksum;
    }
    return 0;
}