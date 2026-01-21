int main() {
    Solution sol;
    vector<TestCase> tests = {
        {{5}, {-1}},
        {{0}, {-1}},
        {{12}, {-1}},
        {{11}, {-1}},
        {{123456789}, {-1}},
        {{101}, {-1}},
        {{24680}, {-1}},
        {{987654321}, {-1}},
        {{4444}, {-1}},
        {{13579}, {-1}}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.goodSubtreeSum(const_cast<vector<int>&>(t.vals), const_cast<vector<int>&>(t.par));
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}