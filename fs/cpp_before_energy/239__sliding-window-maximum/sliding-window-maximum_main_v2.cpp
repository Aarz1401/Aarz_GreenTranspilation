int main() {
    vector<TestCase> tests = {
        {{1}, 1},
        {{4, -1, 7, 7, 5}, 1},
        {{1, 3, 2, 5, 4}, 5},
        {{1, 2, 3, 4, 5, 6}, 3},
        {{6, 5, 4, 3, 2, 1}, 2},
        {{2, 2, 2, 2, 2}, 3},
        {{-5, -2, -3, -1, -4}, 2},
        {{1000000000, 500000000, 1000000000, -1000000000, 0}, 3},
        {{9, 9, 1, 3, 7, 2, 6, 5}, 4},
        {{1, 3, -1, -3, 5, 3, 6, 7, 0, 2, 9, -8, 4, 4, 10}, 5}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            vector<int> out = sol.maxSlidingWindow(t.nums, t.k);
            for (int v : out) {
                checksum ^= v;
            }
        }
        sink = checksum;
    }

    return 0;
}