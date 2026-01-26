int main() {
    vector<vector<int>> tests = {
        {1},
        {1, 2},
        {2, 1, 5, 7, 2, 0, 5},
        {-5, -10, -3, -4, -1},
        {100, 100, 100, 100, 100},
        {5, 4, 3, 2, 1, 0},
        {0, -1, 1, -2, 2, -3, 3},
        {10, 20, 30, 40, 50, 60, 70, 80},
        {3, 3, 4, 2, 2, 1, 5, 5, 6},
        {7, 0, 0, 7, -7, 14, -14, 7, -7, 0}
    };

    volatile int sink = 0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            MedianFinder mf;
            for (int x : t) {
                mf.addNum(x);
            }
            checksum += static_cast<int>(mf.findMedian());
        }
        sink = checksum;
    }
    return 0;
}