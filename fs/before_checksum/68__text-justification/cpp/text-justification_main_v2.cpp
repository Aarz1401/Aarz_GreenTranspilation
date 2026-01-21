int main() {
    std::vector<Case> tests = {
        {{"Hello"}, 5},
        {{"Hi"}, 4},
        {{"This","is","an","example","of","text","justify"}, 16},
        {{"a","b","c"}, 6},
        {{"lorem","ipsum","dolor","sit","amet","consect","adipis"}, 14},
        {{"a","group","of","words","to","fill","the","last","line"}, 12},
        {{"aa","bb","cc","dd"}, 11},
        {{"a","b","c","d"}, 1},
        {{"longword","tiny","mid","size","words","here"}, 10},
        {{"abc","def","ghi"}, 11}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            std::vector<std::string> words = tc.words;
            std::vector<std::string> res = sol.fullJustify(words, tc.width);
            for (const auto& line : res) {
                checksum += static_cast<int>(line.size());
                checksum += static_cast<unsigned char>(line[0]);
                checksum += static_cast<unsigned char>(line[line.size() - 1]);
            }
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}