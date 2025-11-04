#include <iostream>
#include <vector>
#include <array>
#include <deque>
#include <utility>
#include <algorithm>
#include <chrono>

using namespace std;

// Time:  O(n^3)
// Space: O(n^2)
class Solution {
public:
    int catMouseGame(vector<vector<int>>& graph) {
        const int HOLE = 0, MOUSE_START = 1, CAT_START = 2;
        const int DRAW = 0, MOUSE = 1, CAT = 2;

        const int n = static_cast<int>(graph.size());

        // degree[m][c][t]: number of outgoing moves from state (m, c, t)
        vector<vector<array<int, 3>>> degree(n, vector<array<int, 3>>(n, {0, 0, 0}));
        // color[m][c][t]: 0 (DRAW), 1 (MOUSE win), 2 (CAT win)
        vector<vector<array<int, 3>>> color(n, vector<array<int, 3>>(n, {0, 0, 0}));

        // preprocess: set of neighbors of HOLE to check if cat can move to HOLE
        vector<int> ignore(n, 0);
        for (int v : graph[HOLE]) {
            ignore[v] = 1;
        }

        for (int m = 0; m < n; ++m) {
            for (int c = 0; c < n; ++c) {
                degree[m][c][MOUSE] = static_cast<int>(graph[m].size());
                // cat cannot move to HOLE
                degree[m][c][CAT] = static_cast<int>(graph[c].size()) - (ignore[c] ? 1 : 0);
            }
        }

        struct Node { int m, c, t, w; };
        deque<Node> q;

        // Initialize terminal states
        for (int i = 0; i < n; ++i) {
            if (i == HOLE) continue;
            color[HOLE][i][CAT] = MOUSE;
            q.push_back({HOLE, i, CAT, MOUSE});
            for (int t : {MOUSE, CAT}) {
                color[i][i][t] = CAT;
                q.push_back({i, i, t, CAT});
            }
        }

        while (!q.empty()) {
            auto cur = q.front(); q.pop_front();
            int i = cur.m, j = cur.c, t = cur.t, w = cur.w;

            if (t == CAT) {
                // parents: (nm, j, MOUSE) where nm in graph[i]
                for (int nm : graph[i]) {
                    int ni = nm, nj = j, nt = MOUSE;
                    if (color[ni][nj][nt] != DRAW) continue;
                    if (nt == w) {
                        color[ni][nj][nt] = w;
                        q.push_back({ni, nj, nt, w});
                    } else {
                        if (--degree[ni][nj][nt] == 0) {
                            color[ni][nj][nt] = w;
                            q.push_back({ni, nj, nt, w});
                        }
                    }
                }
            } else {
                // parents: (i, nc, CAT) where nc in graph[j] and nc != HOLE
                for (int nc : graph[j]) {
                    if (nc == HOLE) continue;  // cat cannot move to hole
                    int ni = i, nj = nc, nt = CAT;
                    if (color[ni][nj][nt] != DRAW) continue;
                    if (nt == w) {
                        color[ni][nj][nt] = w;
                        q.push_back({ni, nj, nt, w});
                    } else {
                        if (--degree[ni][nj][nt] == 0) {
                            color[ni][nj][nt] = w;
                            q.push_back({ni, nj, nt, w});
                        }
                    }
                }
            }
        }

        return color[MOUSE_START][CAT_START][MOUSE];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse test graphs
    vector<vector<vector<int>>> tests = {
        // G1: triangle
        { {1,2}, {0,2}, {0,1} },
        // G2: chain of 4
        { {1}, {0,2}, {1,3}, {2} },
        // G3: star centered at 0 (hole)
        { {1,2,3,4}, {0}, {0}, {0}, {0} },
        // G4: complete graph of 5
        { {1,2,3,4}, {0,2,3,4}, {0,1,3,4}, {0,1,2,4}, {0,1,2,3} },
        // G5: LeetCode-like example (often a draw)
        { {2,5}, {3}, {0,4,5}, {1,4,5}, {2,3}, {0,2,3} },
        // G6: ring of 6
        { {1,5}, {0,2}, {1,3}, {2,4}, {3,5}, {4,0} },
        // G7: two components, one isolated node
        { {1}, {0}, {3}, {2}, {} },
        // G8: chain of 3
        { {1}, {0,2}, {1} },
        // G9: small star - cat adjacent only to hole
        { {1,2}, {0}, {0} },
        // G10: dense irregular graph of 7
        { {1,2,3}, {0,4,5}, {0,4,6}, {0,5,6}, {1,2,5,6}, {1,3,4,6}, {2,3,4,5} }
    };

    Solution sol;
    volatile long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.catMouseGame(tests[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, std::milli> elapsed = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";

    return 0;
}