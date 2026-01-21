int main() {
    vector<string> tests = {
        "1",
        "0",
        "999",
        "36",
        "4444",
        "888",
        "77777",
        "1234567890",
        "5050505050",
        "3141592653589793238462643383279"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += static_cast<int>(sol.countSubstrings(s));
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}