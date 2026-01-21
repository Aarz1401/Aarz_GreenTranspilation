int main() {
    vector<Test> tests = {
        {"abcde", "a*b*e"},
        {"aaabbbccc", "a*b*c"},
        {"xxabyybczzc", "ab*bc*c"},
        {"ababababa", "aba*bab*aba"},
        {"thequickbrownfoxjumpsoverthelazydog", "the*own*dog"},
        {"aaaaabaaaaacaaaaad", "aaa*ba*ad"},
        {"cabxxabcxxabcc", "ca*ab*cc"},
        {"mississippi", "mi*si*pi"},
        {"xyzxyzxyz", "xy*zz*yz"},
        {"aaabaaaaaccc", "aaab*aaaa*cc"}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.shortestMatchingSubstring(t.s, t.p);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}