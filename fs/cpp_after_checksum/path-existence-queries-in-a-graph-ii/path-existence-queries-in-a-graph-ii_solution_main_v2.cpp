int main() {
    vector<TestCase> tests;
    tests.reserve(10);

    tests.push_back(TestCase{
        1,
        {5},
        0,
        {{0, 0}}
    });

    tests.push_back(TestCase{
        2,
        {1, 2},
        1,
        {{0, 1}, {1, 0}}
    });

    tests.push_back(TestCase{
        2,
        {1, 5},
        2,
        {{0, 1}, {0, 0}, {1, 1}}
    });

    tests.push_back(TestCase{
        5,
        {10, 10, 10, 10, 10},
        0,
        {{0, 4}, {1, 3}, {2, 2}}
    });

    tests.push_back(TestCase{
        6,
        {1, 4, 7, 10, 13, 16},
        3,
        {{0, 5}, {2, 4}, {1, 3}}
    });

    tests.push_back(TestCase{
        6,
        {1, 100, 2, 101, 3, 102},
        2,
        {{0, 2}, {1, 5}, {0, 5}}
    });

    tests.push_back(TestCase{
        8,
        {5, 1, 6, 2, 7, 3, 8, 4},
        1,
        {{7, 0}, {3, 4}, {1, 6}}
    });

    tests.push_back(TestCase{
        10,
        {0, 2, 4, 6, 100, 102, 104, 1000, 1002, 1004},
        3,
        {{0, 3}, {4, 6}, {7, 9}, {0, 9}, {3, 4}}
    });

    tests.push_back(TestCase{
        5,
        {50, 40, 30, 20, 10},
        15,
        {{0, 4}, {1, 3}, {2, 2}}
    });

    tests.push_back(TestCase{
        7,
        {3, 9, 12, 20, 21, 30, 31},
        5,
        {{1, 2}, {3, 4}, {0, 6}, {5, 6}}
    });

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (auto& t : tests) {
            vector<int> res = sol.pathExistenceQueries(t.n, t.nums, t.maxDiff, t.queries);
            for (int v : res) checksum += v;
            checksum += (int)res.size();
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}