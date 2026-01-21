int main() {
    std::vector<std::vector<int>> tests = {
        {1, 2, 3, 4},
        {1, 1, 1, 2},
        {1, 3, 5, 7},
        {1, 3, 2, 6, 5, 4},
        {0, 2, 4, 3, 1},
        {9998, 10000, 9999},
        {10, 100, 1000, 10000},
        {1, 4, 7, 2, 3, 5, 6},
        {5, 5, 7, 9, 8, 6},
        {42}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& tc : tests) {
            SummaryRanges sr;
            for (int v : tc) {
                sr.addNum(v);
            }
            auto res = sr.getIntervals();
            checksum += static_cast<int>(res.size());
            for (const auto& r : res) {
                checksum += r[0] + r[1];
            }
        }
        sink = checksum;
    }
    return 0;
}