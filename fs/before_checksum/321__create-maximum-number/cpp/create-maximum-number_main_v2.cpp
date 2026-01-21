int main() {
    Solution sol;
    vector<TestCase> tests = {
        {{3,4,6,5}, {9,1,2,5,8,3}, 5},
        {{6,7}, {6,0,4}, 5},
        {{3,9}, {8,9}, 3},
        {{1,2,3,4,5}, {5,4,3,2,1}, 5},
        {{9,9,9,9}, {9,9,9}, 6},
        {{1}, {2,3,4,5,6,7,8,9}, 4},
        {{8,6,9}, {1,7,5}, 5},
        {{2,5,6,4,4,0}, {7,3,8,0,6,5,7,6,2}, 15},
        {{5,2,1,9,0}, {3,9,5,6}, 6},
        {{0,0,0,0,0,0}, {0,0,0,0}, 7}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& tc : tests) {
            auto res = sol.maxNumber(tc.a, tc.b, tc.k);
            int s = 0;
            for (int v : res) s += v;
            checksum += s;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}