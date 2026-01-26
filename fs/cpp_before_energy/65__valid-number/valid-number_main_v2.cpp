int main() {
    std::vector<std::string> tests = {
        "0",
        " 0.1 ",
        "-90E3",
        "3.",
        ".5",
        "+.8",
        "6e-1",
        "53.5e93",
        "-.7e+2",
        " 005047e+6 "
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.isNumber(s);
        }
        sink = checksum;
    }

    return 0;
}