int main() {
    std::vector<TestCase> tests = {
        { {5,5,5,5}, 0, 0 },
        { {1,2,3,4,5}, 0, 2 },
        { {1,1,2,2,3,3}, 1, 2 },
        { {10,20,30,40,50}, 100, 1 },
        { {-5,-3,-1,0,2,4}, 2, 3 },
        { {7}, 0, 100 },
        { {1,1,1,2,2,4,4,4,4,5,6,6,6,7,7,8}, 0, 1000 },
        { {1000000000, -1000000000, 0, 999999999, -999999999}, 2000000000, 2 },
        { {1,2,2,2,5,5,8,9,10}, 3, 2 },
        { {0,1,3,6,10,15,21,28,36,45}, 4, 5 }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            std::vector<int> nums = tc.nums;
            checksum += sol.maxFrequency(nums, tc.k, tc.ops);
        }
        sink = checksum;
    }

    return 0;
}