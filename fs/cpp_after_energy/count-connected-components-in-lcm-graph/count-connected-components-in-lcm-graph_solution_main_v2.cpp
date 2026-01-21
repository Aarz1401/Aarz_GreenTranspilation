int main() {
    vector<TestInput> tests = {
        {{1}, 1},
        {{2, 3, 5}, 6},
        {{2, 4, 6, 8, 10}, 10},
        {{7, 14, 21, 28, 35}, 36},
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10},
        {{11, 22, 33}, 10},
        {{5, 5, 5, 5}, 5},
        {{4, 9, 16, 25, 36}, 40},
        {{12, 1, 6, 3, 9}, 12},
        {{100, 50, 25, 20, 10, 5, 4, 2, 1}, 100}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < (int)tests.size(); ++i) {
            checksum += sol.countComponents(tests[i].nums, tests[i].threshold);
        }
        sink = checksum;
    }
    return 0;
}