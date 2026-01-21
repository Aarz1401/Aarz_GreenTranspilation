int main() {
    vector<string> tests = {
        "abc",
        "zzz",
        "azbycxd",
        "helloworld",
        "abcdefghijklmnopqrstuvwxyz",
        "qwertyuiopasdfghjklzxcvbnm",
        "aaaaabbbbbcccccdddddeeeee",
        "mmmmmm",
        "nyanpasu",
        "babababababababababa"
    };

    Solution sol;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& s : tests) {
            string r = sol.minCostGoodCaption(s);
            checksum += static_cast<int>(r[0]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}