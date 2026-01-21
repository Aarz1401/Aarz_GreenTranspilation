int main() {
    Solution sol;

    std::vector<TestCase> tests = {
        {1, 1, 0},    // minimal case
        {2, 3, 0},    // small, K=0
        {3, 3, 1},    // L==N, K>0
        {3, 2, 0},    // L<N -> 0
        {4, 10, 2},   // moderate
        {7, 12, 5},   // K close to N
        {10, 10, 0},  // L==N, K=0
        {10, 20, 2},  // larger L
        {20, 50, 5},  // larger N and L
        {50, 100, 10} // heavier case
    };

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    unsigned long long checksum = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            checksum += static_cast<unsigned long long>(sol.numMusicPlaylists(t.N, t.L, t.K));
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (us): " << elapsed_us << "\n";

    return 0;
}