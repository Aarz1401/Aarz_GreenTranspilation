int main() {
    Solution s;
    std::vector<int> tests = {0, 1, 2, 3, 5, 8, 21, 144, 1000, 1000000000};

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (int x : tests) {
            checksum += s.findIntegers(x);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;
    return 0;
}