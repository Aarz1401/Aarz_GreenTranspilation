int main() {
    vector<vector<vector<int>>> tests = {
        {{1}},
        {{1,2}},
        {{1,0},{3,2}},
        {{1,2,3},{0,0,0},{7,6,5}},
        {{1,2,3,4},{0,0,5,0},{8,7,6,9},{0,0,0,10}},
        {{1,1,1,1,1},{0,0,0,0,1},{1,2,3,4,5},{1,0,0,0,0},{6,7,8,9,10}},
        {{1,1},{1,1}},
        {{1,3,5},{2,8,4},{7,6,9}},
        {{1,2,3,4,5,6},{0,0,0,0,0,7},{12,11,10,9,8,14},{13,0,0,0,0,15},{16,17,18,19,20,21},{0,0,0,0,0,22}},
        {{1,0,2,0,3},{4,5,6,0,7},{0,0,8,9,10}}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& forest : tests) {
            checksum += sol.cutOffTree(forest);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}