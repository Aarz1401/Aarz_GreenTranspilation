#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>
#include <array>
using namespace std;
template <class T>
static inline void DoNotOptimize(const T& value) {
    asm volatile("" : : "r,m"(value) : "memory");
}

class Solution {
public:
    long long subtreeInversionSum(vector<vector<int>>& edges, vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<vector<int>> adj(n);
        for (const auto& e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<array<long long, 2>> dp;
        function<tuple<long long, long long, long long>(int, int)> dfs =
            [&](int u, int p) -> tuple<long long, long long, long long> {
                dp.push_back({0LL, 0LL});
                long long total = nums[u];
                long long pos = 0, neg = 0;
                for (int v : adj[u]) {
                    if (v == p) continue;
                    auto [new_total, new_pos, new_neg] = dfs(v, u);
                    total += new_total;
                    pos += new_pos;
                    neg += new_neg;
                }
                pos = max(pos, dp.back()[1] - 2 * total);
                neg = max(neg, dp.back()[0] + 2 * total);
                dp.pop_back();
                if ((int)dp.size() - k >= 0) {
                    dp[dp.size() - k][0] += pos;
                    dp[dp.size() - k][1] += neg;
                }
                return {total, pos, neg};
            };

        auto [total, pos, neg] = dfs(0, -1);
        return total + pos;
    }
};

struct Test {
    vector<vector<int>> edges;
    vector<int> nums;
    int k;
};

int main() {
    vector<Test> tests = {
        // 1) Single node
        { {}, {7}, 1 },
        // 2) Chain of 5
        { {{0,1},{1,2},{2,3},{3,4}}, {3,-1,4,-2,1}, 1 },
        // 3) Balanced binary tree of 7
        { {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6}}, {-5,-4,-3,2,1,0,7}, 2 },
        // 4) Star with 6 nodes
        { {{0,1},{0,2},{0,3},{0,4},{0,5}}, {10,-10,5,-5,2,-2}, 3 },
        // 5) Mixed branching with 8 nodes
        { {{0,1},{1,2},{1,3},{3,4},{3,5},{5,6},{6,7}}, {1,2,3,4,5,6,7,8}, 2 },
        // 6) 10 nodes with zeros and negatives
        { {{0,1},{0,2},{2,3},{2,4},{4,5},{4,6},{1,7},{7,8},{8,9}}, {0,-1,-2,-3,0,3,2,1,-4,5}, 4 },
        // 7) 15-node near-complete binary
        { {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{3,7},{3,8},{4,9},{4,10},{5,11},{5,12},{6,13},{6,14}},
          {-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7}, 5 },
        // 8) 9 nodes with large positives
        { {{0,1},{1,2},{2,3},{2,4},{4,5},{5,6},{3,7},{7,8}}, {100,200,300,400,500,600,700,800,900}, 3 },
        // 9) Small branched 4-node
        { {{0,1},{1,2},{1,3}}, {-1000,0,1000,-500}, 1 },
        // 10) 12-node mixed
        { {{0,1},{0,2},{1,3},{1,4},{2,5},{2,6},{4,7},{4,8},{6,9},{9,10},{10,11}}, {5,-3,8,-2,7,0,-1,4,-4,6,-6,2}, 6 }
    };

    Solution solver;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        //int checksum = 0;
        for (const auto& t : tests) {
            long long r = solver.subtreeInversionSum(const_cast<vector<vector<int>>&>(t.edges),
                                                     const_cast<vector<int>&>(t.nums),
                                                     t.k);
            DoNotOptimize(r);
            //checksum += static_cast<int>(r);
        }
        //sink = checksum;
    }
    return 0;
}