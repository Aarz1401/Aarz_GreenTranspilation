int main() {
    const vector<vector<int>> tests = {
        {1, 3, 2, 3, 1},
        {2, 4, 3, 5, 1},
        {1, 2, 3, 4, 5, 6},
        {6, 5, 4, 3, 2, 1},
        {-5, -2, -1, 0, 1, 2, 3},
        {2000000000, -1000000000, 1000000000, -500000000, 0},
        {-1, -2, -3, -4, -5},
        {1, 10, 2, 9, 3, 8, 4, 7, 5, 6},
        {9, 1, 3, 2, 3, 1, 5, 0, -1, 8},
        {-100000000, 50000000, -25000000, 12500000, -6250000, 3125000, -1562500, 781250, -390625, 195312, -97656, 48828, -24414, 12207, -6103, 3051, -1525, 762, -381, 190, -95, 47, -23, 11, -5, 2, -1, 0, 1, 3}
    };

    const int iterations = 1000;
    volatile int sink = 0;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        Solution sol;
        for (const auto& t : tests) {
            vector<int> nums = t;
            checksum += sol.reversePairs(nums);
        }
        sink = checksum;
    }

    return 0;
}