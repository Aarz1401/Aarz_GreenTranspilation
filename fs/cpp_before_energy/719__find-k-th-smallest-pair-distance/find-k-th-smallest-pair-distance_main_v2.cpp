int main() {
    struct Test {
        std::vector<int> nums;
        int k;
    };

    std::vector<Test> tests = {
        {{1, 100}, 1},
        {{1, 3, 1}, 1},
        {{1, 2, 3, 4, 5}, 4},
        {{10, 10, 10, 10}, 6},
        {{1, 6, 1, 2, 5, 9}, 7},
        {{0, 0, 0, 0, 0, 0}, 10},
        {{0, 1000000}, 1},
        {{1, 1, 2, 2, 3, 3, 4, 4}, 16},
        {{1, 3, 6, 10, 15, 21, 28, 36}, 20},
        {{4, 1, 4, 2, 8, 5, 7, 2, 3}, 12}
    };

    Solution solution;

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            std::vector<int> nums = t.nums;
            int result = solution.smallestDistancePair(nums, t.k);
            checksum += result;
        }
        sink = checksum;
    }

    return 0;
}