int main() {
    std::vector<TestCase> tests = {
        { {7, 2, 5, 10, 8}, 2 },
        { {5}, 1 },
        { {1, 1, 1, 1, 1}, 5 },
        { {1, 2, 3, 4, 5, 6, 7, 8, 9}, 3 },
        { {1000000, 1000000, 1000000, 1000000}, 2 },
        { {2, 3, 1, 2, 4, 3}, 1 },
        { {9, 8, 7, 6}, 4 },
        { {5, 1, 8, 3, 2, 7, 4, 6, 9, 10, 11, 13, 12, 14, 15, 16, 18, 17, 19, 20}, 5 },
        { {0, 0, 0, 0, 0, 10}, 3 },
        { {100, 1, 100, 1, 100, 1, 100, 1, 100, 1}, 3 }
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += sol.splitArray(t.nums, t.m);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}