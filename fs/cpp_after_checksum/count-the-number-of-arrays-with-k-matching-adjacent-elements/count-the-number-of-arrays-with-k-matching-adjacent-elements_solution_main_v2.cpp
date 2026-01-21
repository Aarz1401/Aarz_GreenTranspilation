int main() {
    vector<array<int, 3>> tests = {
        array<int,3>{1, 1, 0},
        array<int,3>{2, 1, 1},
        array<int,3>{2, 1, 0},
        array<int,3>{5, 2, 0},
        array<int,3>{5, 2, 4},
        array<int,3>{7, 100, 3},
        array<int,3>{10, 3, 5},
        array<int,3>{50, 1000000007, 0},
        array<int,3>{200000, 100000, 99999},
        array<int,3>{200000, 1, 199999}
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto &t : tests) {
            int res = sol.countGoodArrays(t[0], t[1], t[2]);
            checksum ^= res;
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}