int main() {
    std::vector<Test> tests = {
        { {-2, 5, -1}, -2, 2 },
        { {1, 2, 3, 4}, 3, 6 },
        { {-1, -2, -3}, -5, -2 },
        { {0, 0, 0}, 0, 0 },
        { {5}, 5, 5 },
        { {2147483647, -2147483647, 2147483647}, 2147483647, 2147483647 },
        { {3, -1, 2, -2, 5, -3, 1, -4, 2}, -1, 3 },
        { {-1000, -1000, -1000, -1000, -1000}, -3000, -1000 },
        { {1000000000, -1000000000, 1000000000, -1000000000, 1}, -1, 1 },
        { {7, -5, 4, -2, 8, -6, 3, -1, 0, 2}, 0, 8 }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            checksum += sol.countRangeSum(t.nums, t.lower, t.upper);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}