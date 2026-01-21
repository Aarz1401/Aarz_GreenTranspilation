int main() {
    vector<pair<string, int>> tests;
    tests.emplace_back("0", 0);
    tests.emplace_back("1", 1);
    tests.emplace_back("00", 0);
    tests.emplace_back("01", 0);
    tests.emplace_back("010101010101010", 0);
    tests.emplace_back("0010110100110", 2);
    tests.emplace_back("11111111111111111111", 5);
    tests.emplace_back("000111000111000111000111000111", 4);
    tests.emplace_back("10110011100011110000", 2);
    string longRun;
    longRun.reserve(200);
    for (int i = 0; i < 25; ++i) longRun += "11110000";
    tests.emplace_back(longRun, 20);

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            checksum += sol.minLength(tc.first, tc.second);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}