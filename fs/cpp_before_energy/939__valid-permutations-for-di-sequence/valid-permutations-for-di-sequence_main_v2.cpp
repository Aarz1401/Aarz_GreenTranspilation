int main() {
    std::vector<std::string> tests = {
        "I",
        "D",
        "ID",
        "DI",
        "IID",
        "DDI",
        "IDIDID",
        "DDDDIIII",
        "IIDDDIII",
        "IDDIIDIDID"
    };

    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.numPermsDISequence(s);
        }
        sink = checksum;
    }

    return 0;
}