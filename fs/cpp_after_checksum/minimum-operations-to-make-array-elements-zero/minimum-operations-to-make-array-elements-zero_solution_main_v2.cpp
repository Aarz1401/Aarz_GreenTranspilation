int main() {
    vector<vector<vector<int>>> tests = {
        { {1, 1} },
        { {4, 4} },
        { {2, 5} },
        { {1, 16} },
        { {1, 3}, {4, 7}, {8, 15} },
        { {10, 100} },
        { {5, 5}, {6, 20}, {21, 64} },
        { {1, 1000000} },
        { {2147483600, 2147483647} },
        { {123456, 123789}, {999999, 1000010} }
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& qs : tests) {
            long long res = sol.minOperations(qs);
            checksum += static_cast<int>(res);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}