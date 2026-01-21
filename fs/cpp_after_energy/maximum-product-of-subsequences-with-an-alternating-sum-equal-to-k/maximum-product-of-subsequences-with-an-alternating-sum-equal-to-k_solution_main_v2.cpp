int main() {
    vector<Test> tests = {
        {{1, 2, 3}, 1, 10},
        {{3, 1, 4, 2}, 4, 100},
        {{0, 0, 5}, 0, 0},
        {{2, 2, 2, 2}, 0, 10},
        {{6, 2, 3}, 4, 20},
        {{7}, 7, 6},
        {{5, 1, 2, 3}, 6, 10},
        {{1, 0, 2, 0}, 1, 5},
        {{10, 5, 1}, 5, 50},
        {{1, 2}, 5, 100}
    };

    Solution sol;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        int checksum = 0;
        for (const auto& t : tests) {
            vector<int> arr = t.nums;
            int res = sol.maxProduct(arr, t.k, t.limit);
            checksum += res;
        }
        sink = checksum;
    }

    return 0;
}