#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <chrono>

using namespace std;
using namespace std::chrono;

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
    vector<TestCase> tests;

    tests.push_back(TestCase{
        1,
        {},
        {7}
    });

    tests.push_back(TestCase{
        2,
        {{0,1}},
        {1, 2}
    });

    tests.push_back(TestCase{
        3,
        {{0,1},{0,2}},
        {-5, 3, 4}
    });

    tests.push_back(TestCase{
        3,
        {},
        {5, -1, 2}
    });

    tests.push_back(TestCase{
        4,
        {{0,1},{1,2},{2,3}},
        {3, 1, 4, 2}
    });

    tests.push_back(TestCase{
        4,
        {{0,1},{0,2},{1,3},{2,3}},
        {2, 5, -1, 4}
    });

    tests.push_back(TestCase{
        4,
        {{0,1},{2,3}},
        {1, 2, 3, 4}
    });

    tests.push_back(TestCase{
        4,
        {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}},
        {-1, -2, -3, -4}
    });

    tests.push_back(TestCase{
        4,
        {{1,2},{1,3}},
        {0, 0, 10, -10}
    });

    tests.push_back(TestCase{
        4,
        {{0,2},{1,2},{1,3}},
        {100, -100, 50, 0}
    });

    Solution sol;

    long long checksum = 0;
    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t idx = 0; idx < tests.size(); ++idx) {
            checksum += sol.maxProfit(tests[idx].n, tests[idx].edges, tests[idx].score);
        }
    }

    auto end = high_resolution_clock::now();
    auto duration_ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed (ns): " << duration_ns << "\n";

    return 0;
}