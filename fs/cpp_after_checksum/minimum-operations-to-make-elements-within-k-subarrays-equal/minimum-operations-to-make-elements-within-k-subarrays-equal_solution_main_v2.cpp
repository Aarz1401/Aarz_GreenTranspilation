int main() {
    vector<Test> tests = {
        {{1, 2, 3, 4, 5}, 1, 2},
        {{1, 10, 1, 10, 1, 10}, 2, 3},
        {{1, 2, 3, 100, 100, 100, 4, 5}, 3, 2},
        {{-5, -1, -3, -2, 100, 101, 102, 103, 0, 0}, 4, 2},
        {{7, 7, 7, 1, 2, 3, 7, 7, 7}, 3, 3},
        {{1, 100, 100, 100, 100, 1, 1, 1, 1, 1, 1, 50}, 5, 2},
        {{0, -1, -2, -3, 4, 5, -6}, 2, 2},
        {{10, 10, 10, 20, 20, 19, 30, 31, 32, 5, 5, 5, 100, 100, 100}, 3, 4},
        {{1, 2, 100, 2, 1, 50, 50, 50, 50, 50}, 5, 2},
        {{8, 1, 9, 2, 7, 3, 6, 4, 5, 0, 5, 0, 100, -100, 100, -100, 50, 51, 49, 50}, 4, 3}
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            long long res = sol.minOperations(const_cast<vector<int>&>(t.nums), t.x, t.k);
            checksum += static_cast<int>(res);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}