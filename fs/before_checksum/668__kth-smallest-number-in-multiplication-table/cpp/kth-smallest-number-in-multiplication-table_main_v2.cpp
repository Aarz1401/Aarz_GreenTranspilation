int main() {
    std::vector<std::array<int, 3>> tests = {
        std::array<int,3>{1, 1, 1},
        std::array<int,3>{1, 10, 7},
        std::array<int,3>{10, 1, 4},
        std::array<int,3>{3, 3, 5},
        std::array<int,3>{2, 3, 6},
        std::array<int,3>{15, 20, 150},
        std::array<int,3>{20, 15, 213},
        std::array<int,3>{43, 47, 1000},
        std::array<int,3>{100, 100, 1000},
        std::array<int,3>{200, 150, 12345}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.findKthNumber(t[0], t[1], t[2]);
        }
        sink += checksum;
        

    } std::cout << sink << std::endl;

    return 0;
}