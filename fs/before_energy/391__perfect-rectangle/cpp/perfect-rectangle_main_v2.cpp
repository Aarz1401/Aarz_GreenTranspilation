int main() {
    vector<vector<vector<int>>> tests = {
        // 1) Single rectangle (true)
        { {0, 0, 2, 3} },
        // 2) 2x2 covered by four 1x1 tiles (true)
        { {0,0,1,1}, {1,0,2,1}, {0,1,1,2}, {1,1,2,2} },
        // 3) Overlapping rectangles (false)
        { {0,0,2,2}, {1,1,3,3} },
        // 4) Gap: three of the four tiles (false)
        { {0,0,1,1}, {1,0,2,1}, {0,1,1,2} },
        // 5) Duplicate rectangle (false)
        { {0,0,1,1}, {0,0,1,1} },
        // 6) Mixed tiling covering [0,0,3,2] (true)
        { {0,0,1,2}, {1,0,2,1}, {1,1,2,2}, {2,0,3,2} },
        // 7) Negative coordinates perfect cover [-3,-1,2,3] (true)
        { {-3,-1,-1,3}, {-1,-1,2,1}, {-1,1,2,3} },
        // 8) Large coordinates within typical constraints (true)
        { {10000,10000,15000,15000}, {15000,10000,20000,15000},
          {10000,15000,15000,20000}, {15000,15000,20000,20000} },
        // 9) Another perfect cover [0,0,4,3] (true)
        { {0,0,1,3}, {1,0,4,1}, {1,1,4,3} },
        // 10) Gap near edge in [0,0,3,2] (false)
        { {0,0,2,2}, {2,0,3,1} }
    };

    Solution sol;

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& recs : tests) {
            checksum += sol.isRectangleCover(recs);
        }
        sink = checksum;
    }
    return 0;
}