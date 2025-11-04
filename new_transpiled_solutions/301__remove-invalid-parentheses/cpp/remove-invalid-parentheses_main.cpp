int main() {
    std::vector<std::string> test_inputs = {
        "()",
        ")(",
        "(a)())()",
        "(()",
        "())())",
        "(((k)))",
        "(a(b(c)d)e)f)",
        "",
        "abc",
        "((())())(()"
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& s : test_inputs) {
            auto out = sol.removeInvalidParentheses(s);
            checksum += static_cast<unsigned long long>(out.size());
            for (const auto& t : out) {
                // FNV-1a hash to incorporate content into checksum
                unsigned long long h = 1469598103934665603ull;
                for (unsigned char c : t) {
                    h ^= c;
                    h *= 1099511628211ull;
                }
                // mix into checksum
                checksum ^= h + 0x9e3779b97f4a7c15ull + (checksum << 6) + (checksum >> 2);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}