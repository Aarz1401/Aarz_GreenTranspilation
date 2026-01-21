int main() {
    vector<vector<int>> tests;
    tests.reserve(10);
    tests.push_back({1, 2, 3});
    tests.push_back({5});
    tests.push_back({2, 2, 2});
    tests.push_back({1, 2, 1, 2, 3, 3});
    {
        vector<int> t5;
        t5.reserve(50);
        for (int i = 0; i < 50; ++i) t5.push_back(i % 2);
        tests.push_back(t5);
    }
    tests.push_back({0, 0, 0, 1, 1, 2, 2, 2});
    tests.push_back({5, 3, 5, 2, 5, 2, 3, 4, 5, 6, 7, 8, 5, 9});
    {
        vector<int> t8;
        t8.reserve(20);
        for (int i = 1; i <= 20; ++i) t8.push_back(i);
        tests.push_back(t8);
    }
    {
        vector<int> t9;
        t9.reserve(20);
        for (int i = 1; i <= 10; ++i) { t9.push_back(i); t9.push_back(i); }
        tests.push_back(t9);
    }
    {
        vector<int> t10;
        t10.reserve(45);
        for (int i = 0; i < 30; ++i) t10.push_back(0);
        for (int i = 0; i < 10; ++i) t10.push_back(1);
        for (int i = 0; i < 5; ++i) t10.push_back(2);
        tests.push_back(t10);
    }

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int i = 0; i < 10; ++i) {
            checksum += sol.subsequencesWithMiddleMode(tests[i]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}