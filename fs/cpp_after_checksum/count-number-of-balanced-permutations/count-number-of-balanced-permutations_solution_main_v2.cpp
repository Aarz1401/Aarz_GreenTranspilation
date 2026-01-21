int main() {
    vector<string> tests = {
        "5",
        "11",
        "1234",
        "0000",
        "9999",
        "121",
        "0123456789",
        "0001234567",
        "2468",
        "13579"
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.countBalancedPermutations(s);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}