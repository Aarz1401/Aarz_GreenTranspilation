int main() {
    vector<int> tests = {
        0,
        1,
        4,
        5,
        10,
        25,
        29,
        30,
        123456789,
        1000000000
    };

    Solution s;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int k : tests) {
            checksum += s.preimageSizeFZF(k);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}