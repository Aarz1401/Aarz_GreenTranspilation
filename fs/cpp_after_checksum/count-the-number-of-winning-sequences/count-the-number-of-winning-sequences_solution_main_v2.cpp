int main() {
    vector<string> tests = {
        "F",
        "W",
        "E",
        "FW",
        "WEF",
        "FFWE",
        "FWEFWE",
        "EEEEWWWWFFFF",
        "FEWEWFEWFWEE",
        "FWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWEFWE"
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.countWinningSequences(s);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}