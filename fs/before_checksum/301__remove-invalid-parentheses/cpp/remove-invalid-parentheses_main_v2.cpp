int main() {
    std::vector<std::string> inputs = {
        "()())()",
        "(a)())()",
        ")(",
        "(((",
        "abcde",
        "((a)(b))",
        "((())",
        "())((()a)",
        "n)()(m)",
        "(((x)))(y))("
    };

    volatile int sink = 0;
    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : inputs) {
            auto res = sol.removeInvalidParentheses(s);
            checksum += static_cast<int>(res.size());
            for (const auto& t : res) {
                checksum += static_cast<int>(t.size());
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}