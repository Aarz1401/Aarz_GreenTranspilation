int main() {
    Solution s;
    vector<pair<string, int>> tests = {
        {"123", 6},
        {"232", 8},
        {"105", 5},
        {"00", 0},
        {"345", 17},
        {"999", -9},
        {"1234", 21},
        {"123", 123},
        {"1111", 4},
        {"246", 12}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            auto res = s.addOperators(t.first, t.second);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}