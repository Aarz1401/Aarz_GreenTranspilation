int main() {
    Solution sol;
    vector<string> tests = {
        "a",
        "abc",
        "aaa",
        "abacaba",
        "zzzzzzzzzz",
        "thequickbrownfox",
        "abcdefghijklmnopqrstuvwxyz",
        "aaabbbcccdddeeefffggghhhiiijjj",
        "abababababababababab",
        "qwertyqwertyqwertyqwertyqwerty"
    };

    volatile int sink = 0;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            checksum += sol.makeStringGood(s);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}