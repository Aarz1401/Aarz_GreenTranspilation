int main() {
    Solution sol;

    vector<pair<string, string>> tests = {
        {"TFTFTF", "ab"},
        {"FFFFF", "xyz"},
        {"TTTTT", "aaaa"},
        {"TFTFT", "abab"},
        {"FTTFFTTF", "abcabc"},
        {"F", "z"},
        {"T", "z"},
        {"FFTFFTFF", "aba"},
        {"TFFFFT", "aaaaa"},
        {"TFTF", "a"}
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            string out = sol.generateString(tc.first, tc.second);
            checksum += static_cast<int>(out.size());
            if (!out.empty()) {
                checksum += static_cast<unsigned char>(out.front());
                checksum += static_cast<unsigned char>(out.back());
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}