int main() {
    vector<vector<vector<int>>> tests = {
        { {1, 3}, {2} },
        { {1, 2}, {3, 4} },
        { {0, 0, 0, 0}, {1, 2, 3} },
        { {-5, -3, -1}, {-2, 0, 2, 4} },
        { {1, 1, 1, 1, 1}, {1, 1, 2, 2, 2} },
        { {-2147483647, -1000000000, 0, 1000000000, 2147483647}, {-999999999, -1, 1, 999999999} },
        { {1, 3, 5, 7, 9, 11, 13, 15}, {2} },
        { {10}, {20} },
        { {100, 200, 300}, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10} },
        { {1}, {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15} }
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int t = 0; t < static_cast<int>(tests.size()); ++t) {
            vector<int>& a = tests[t][0];
            vector<int>& b = tests[t][1];
            double res = sol.findMedianSortedArrays(a, b);
            checksum += static_cast<int>(res);
        }
        sink = checksum;
    }
    return 0;
}