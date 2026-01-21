int main() {
    std::vector<std::pair<int,int>> tests = {
        {1, 1},
        {2, 1},
        {2, 2},
        {3, 5},
        {4, 9},
        {5, 42},
        {6, 400},
        {7, 2500},
        {8, 40320},
        {9, 362880}
    };

    Solution sol;
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            std::string res = sol.getPermutation(t.first, t.second);
            checksum += static_cast<int>(res[0]);
            checksum += static_cast<int>(res.size());
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}