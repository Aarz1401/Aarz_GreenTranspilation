int main() {
    vector<vector<vector<int>>> tests = {
        {{1,2,3},{4,5,0}},
        {{1,2,3},{4,0,5}},
        {{1,2,0},{4,5,3}},
        {{0,1,2},{3,4,5}},
        {{1,0,2},{3,4,5}},
        {{1,2,3},{5,4,0}},
        {{4,1,2},{3,5,0}},
        {{1,3,4},{2,5,0}},
        {{2,1,3},{4,5,0}},
        {{2,3,4},{1,5,0}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& board : tests) {
            checksum += sol.slidingPuzzle(board);
        }
        sink = checksum;
    }

    return 0;
}