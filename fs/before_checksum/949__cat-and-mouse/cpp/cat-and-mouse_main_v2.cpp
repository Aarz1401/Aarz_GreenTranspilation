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