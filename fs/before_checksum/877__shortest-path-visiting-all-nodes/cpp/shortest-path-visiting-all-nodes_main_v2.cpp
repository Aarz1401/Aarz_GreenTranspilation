int main() {
    vector<vector<vector<int>>> tests = {
        { {} },                                         // n=1
        { {1}, {0} },                                   // n=2
        { {1}, {0,2}, {1} },                            // n=3 path
        { {1,3}, {0,2}, {1,3}, {0,2} },                 // n=4 cycle
        { {1,2,3,4}, {0}, {0}, {0}, {0} },              // n=5 star
        { {1,2,3,4,5}, {0,2,3,4,5}, {0,1,3,4,5},        // n=6 complete
          {0,1,2,4,5}, {0,1,2,3,5}, {0,1,2,3,4} },
        { {1,2}, {0,2,4}, {0,1,3,6}, {2,4},             // n=7 mixed
          {1,3,5}, {4,6}, {5,2} },
        { {1,4}, {0,2,5}, {1,3,6}, {2,7},               // n=8 grid 2x4
          {0,5}, {1,4,6}, {2,5,7}, {3,6} },
        { {1,3}, {0,2,4}, {1,5},                        // n=9 grid 3x3
          {0,4,6}, {1,3,5,7}, {2,4,8},
          {3,7}, {4,6,8}, {5,7} },
        { {1,4}, {0,2}, {1,3}, {2,4},                   // n=10 two 5-cycles + bridge
          {3,0,5}, {6,9,4}, {5,7}, {6,8}, {7,9}, {8,5} }
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.shortestPathLength(tests[i]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}