int main() {
    vector<Test> tests = {
        {{1}, 1},
        {{10, 2}, 2},
        {{12, 34, 5}, 3},
        {{0, 0, 5}, 5},
        {{7, 70, 700}, 7},
        {{3, 30, 34, 5, 9}, 3},
        {{12, 45, 78}, 9},
        {{2, 22, 222, 2222}, 37},
        {{9, 99, 999, 9999}, 9},
        {{1, 2, 12, 123, 1234}, 97}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<int> res = sol.concatenatedDivisibility(const_cast<vector<int>&>(t.nums), t.k);
            for (int x : res) checksum += x;
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}