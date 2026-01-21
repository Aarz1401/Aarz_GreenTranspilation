int main() {
    std::vector<std::string> tests = {
        "1",
        "2",
        "10",
        "11",
        "99",
        "123",
        "1283",
        "1000",
        "9999",
        "12345678987654321"
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            std::string r = sol.nearestPalindromic(s);
            checksum += static_cast<int>(r.size());
            checksum += static_cast<int>(r.front() - '0');
            checksum += static_cast<int>(r.back() - '0');
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}