int main() {
    const vector<string> tests = {
        "1",
        "12",
        "226",
        "*",
        "10",
        "2101",
        "1*0",
        "2*6",
        "11106",
        "*7"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.numDecodings(s);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}