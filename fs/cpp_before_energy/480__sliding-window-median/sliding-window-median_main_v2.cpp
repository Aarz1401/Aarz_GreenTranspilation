int main() {
    vector<Test> tests = {
        {{1, 3, -1, -3, 5, 3, 6, 7}, 3},
        {{1, 3, -1, -3, 5, 3, 6, 7}, 4},
        {{5}, 1},
        {{2, 2, 2, 2, 2, 2}, 3},
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5},
        {{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 2},
        {{0, -1, 1, 0, -2, 2, 0, -3, 3, 0}, 7},
        {{100, -100, 50, -50, 25, -25, 75, -75, 0, 0}, 4},
        {{500, -200, 300, -400, 1000, -1000, 750, -750, 250, -250, 125, -125, 60, -60, 30, -30, 15, -15, 7, -7}, 10},
        {{4, 1, 7, 8, 5, 2, 6, 3, 9}, 9}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            auto nums = t.nums;
            int k = t.k;
            auto res = sol.medianSlidingWindow(nums, k);
            checksum += static_cast<int>(res.size());
            for (double v : res) {
                checksum += static_cast<int>(v);
            }
        }
        sink = checksum;
    }

    return 0;
}