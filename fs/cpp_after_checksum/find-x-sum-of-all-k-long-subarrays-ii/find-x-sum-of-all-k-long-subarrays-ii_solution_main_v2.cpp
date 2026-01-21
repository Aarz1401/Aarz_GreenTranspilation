int main() {
    vector<TestCase> tests = {
        {{1}, 1, 1},
        {{5,5,5,5,5}, 3, 1},
        {{1,2,2,3,3,3,4,4,4,4}, 5, 2},
        {{10,9,8,7,6,5,4,3,2,1}, 4, 3},
        {{1000000000,1000000000,999999999,1000000000,999999999}, 3, 2},
        {{1,1,2,2,2,3,3,4,5,5,5,5,6}, 6, 4},
        {{7,7,7,8,8,9,9,9,9,10,10,10}, 5, 5},
        {{2,3,5,7,11,13,17,19,23,29}, 2, 1},
        {{0,1,0,1,0,1,0,1,0,1,0,1}, 3, 10},
        {{1,2,3,1,2,3,1,2,3,1,2}, 5, 3}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (const auto& t : tests) {
            auto res = sol.findXSum(const_cast<vector<int>&>(t.nums), t.k, t.x);
            for (auto v : res) {
                checksum ^= static_cast<int>(v);
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}