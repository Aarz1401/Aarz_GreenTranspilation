int main() {
    std::vector<std::string> tests = {
        "()",
        ")()())",
        "()(()",
        "((()))",
        "()()()",
        "(((((",
        "))))))",
        "(()())",
        "())((())",
        ")(()())(()())"
    };

    Solution sol;
    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.longestValidParentheses(s);
        }
        sink = checksum;
    }
    return 0;
}