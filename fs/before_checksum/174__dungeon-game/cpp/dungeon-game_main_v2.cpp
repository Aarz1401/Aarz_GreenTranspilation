int main() {
    vector<vector<vector<int>>> tests = {
        {{-1}},
        {{5}},
        {{-2, -3, 3, -1}},
        {{-2}, {-3}, {3}, {-5}},
        {{-2, -2}, {-2, -2}},
        {{1, 2, 3}, {4, 5, 6}},
        {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}},
        {{0, -1, 0, -2}, {1, 0, -3, 0}, {-2, 4, 0, -1}, {0, -2, 3, 0}},
        {{1}, {1}, {1}, {1}, {1}},
        {{-1000, 1000, -1000, 1}, {1, -1, -1, 1000}, {999, -999, 500, -500}}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += sol.calculateMinimumHP(tests[i]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}