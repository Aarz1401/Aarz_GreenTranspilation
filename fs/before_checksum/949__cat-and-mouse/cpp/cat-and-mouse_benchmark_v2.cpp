#include <iostream>
#include <vector>
#include <array>
#include <deque>

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
    vector<vector<vector<int>>> tests = {
        // 1) K3 complete graph on {0,1,2}
        {
            {1,2},
            {0,2},
            {0,1}
        },
        // 2) Path 1-2-0 (mouse at 1 forced into cat at 2)
        {
            {2},
            {2},
            {0,1}
        },
        // 3) Path 0-1-2-3
        {
            {1},
            {0,2},
            {1,3},
            {2}
        },
        // 4) Star centered at 0 with leaves {1,2,3,4}
        {
            {1,2,3,4},
            {0},
            {0},
            {0},
            {0}
        },
        // 5) Mixed 5-node graph
        {
            {2},
            {2,4},
            {0,1,3},
            {2,4},
            {1,3}
        },
        // 6) Complete graph on 5 nodes
        {
            {1,2,3,4},
            {0,2,3,4},
            {0,1,3,4},
            {0,1,2,4},
            {0,1,2,3}
        },
        // 7) Disconnected pairs: (0-2) and (1-3)
        {
            {2},
            {3},
            {0},
            {1}
        },
        // 8) 7-node connected graph
        {
            {1,2},
            {0,3,4},
            {0,4,5},
            {1,6},
            {1,2,6},
            {2,6},
            {3,4,5}
        },
        // 9) 6-cycle
        {
            {1,5},
            {0,2},
            {1,3},
            {2,4},
            {3,5},
            {4,0}
        },
        // 10) Triangle among {1,2,3}, 0 connected only to 2
        {
            {2},
            {2,3},
            {0,1,3},
            {1,2}
        }
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        // Exactly 10 tests
        for (int i = 0; i < 10; ++i) {
            auto graph = tests[i];
            checksum += sol.catMouseGame(graph);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}