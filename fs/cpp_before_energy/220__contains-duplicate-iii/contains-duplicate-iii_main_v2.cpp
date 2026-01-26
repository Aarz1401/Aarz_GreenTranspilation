int main() {
    vector<Test> tests = {
        { {1, 2, 3, 1}, 3, 0 },
        { {1, 0, 1, 1}, 1, 2 },
        { {1, 5, 9, 1, 5, 9}, 2, 3 },
        { {-1, -3, -6, -2}, 2, 2 },
        { {1000000000, -1000000000}, 1, 2000000000 },
        { {1, 1}, 0, 0 },
        { {0, 100, 200, 300}, 10, 50 },
        { {-100, -99, -98, -97}, 1, 1 },
        { {2147483647, 2147483646, -2147483647, -2147483647 - 1}, 3, 1 },
        { {-1, 2147483647, -2147483647 - 1, 0, 1}, 1, 0 }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& test : tests) {
            auto v = test.nums;
            checksum += sol.containsNearbyAlmostDuplicate(v, test.k, test.t) ? 1 : 0;
        }
        sink = checksum;
    }

    return 0;
}