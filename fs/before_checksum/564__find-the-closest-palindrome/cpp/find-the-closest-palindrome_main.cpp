int main() {
    std::vector<std::string> tests = {
        "0",
        "1",
        "9",
        "10",
        "11",
        "99",
        "100",
        "123",
        "123456789",
        "1000000000000000000"
    };

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : tests) {
            std::string res = sol.nearestPalindromic(s);
            std::size_t h = std::hash<std::string>{}(res);
            checksum ^= static_cast<uint64_t>(h) + 0x9e3779b97f4a7c15ULL + static_cast<uint64_t>(res.size());
            if (!res.empty()) {
                checksum ^= static_cast<uint64_t>(static_cast<unsigned char>(res.front()));
                checksum = (checksum << 1) | (checksum >> 63);
                checksum ^= static_cast<uint64_t>(static_cast<unsigned char>(res.back()));
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}