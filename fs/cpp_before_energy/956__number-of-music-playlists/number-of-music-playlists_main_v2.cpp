int main() {
    std::vector<std::array<int, 3>> tests = {
        std::array<int,3>{1, 1, 0},
        std::array<int,3>{2, 2, 1},
        std::array<int,3>{2, 3, 0},
        std::array<int,3>{3, 3, 2},
        std::array<int,3>{3, 4, 1},
        std::array<int,3>{3, 5, 1},
        std::array<int,3>{4, 4, 3},
        std::array<int,3>{4, 6, 2},
        std::array<int,3>{5, 7, 0},
        std::array<int,3>{6, 8, 1}
    };

    Solution sol;
    volatile int sink = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            checksum += sol.numMusicPlaylists(t[0], t[1], t[2]);
        }
        sink = checksum;
    }

    return 0;
}