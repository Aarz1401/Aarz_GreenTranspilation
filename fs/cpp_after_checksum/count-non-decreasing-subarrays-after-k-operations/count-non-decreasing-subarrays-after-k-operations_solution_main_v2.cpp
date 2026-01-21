int main() {
    std::vector<Test> tests = {
        {{5}, 0},
        {{1, 2, 3, 4}, 0},
        {{4, 3, 2, 1}, 0},
        {{3, 1, 2, 1, 2}, 2},
        {{2, 2, 2, 2, 2}, 0},
        {{0, 0, 1, 0, 0}, 3},
        {{1, 5, 2, 6, 3, 7, 4, 8, 5, 9}, 20},
        {{1000000000, 1, 1000000000, 1}, 3000000000LL},
        {{5, 1}, 3},
        {{1, 3, 2, 2, 5, 1, 7, 2, 3}, 5}
    };

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (auto t : tests) {
            long long r = sol.countNonDecreasingSubarrays(t.nums, t.k);
            checksum += static_cast<int>(r);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}