int main() {
    vector<vector<vector<int>>> tests = {
        {{1,3},{1,4},{2,5},{3,5}},
        {{1,2},{4,5},{7,8}},
        {{0,10},{0,9},{1,8},{2,7},{3,6},{4,5}},
        {{5,10}},
        {{1,2},{2,3},{3,4},{4,5}},
        {{10,20},{15,25},{18,22},{21,30},{5,12},{0,3}},
        {{1000000,1000002},{999998,1000001},{500000,700000}},
        {{2,6},{2,7},{2,8},{3,9},{0,5}},
        {{0,1},{1,2},{2,3},{3,4},{4,6},{5,7},{6,8}},
        {{8,10},{1,3},{2,5},{6,9},{4,7},{0,2}}
    };

    Solution sol;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<vector<int>> in = t;
            checksum += sol.intersectionSizeTwo(in);
        }
        sink = checksum;
    }

    return 0;
}