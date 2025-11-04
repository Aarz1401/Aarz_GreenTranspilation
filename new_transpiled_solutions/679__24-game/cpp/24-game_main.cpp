int main() {
    // Define 10 diverse test inputs
    vector<vector<int>> tests = {
        {4, 1, 8, 7},   // true
        {1, 2, 1, 2},   // false
        {3, 3, 8, 8},   // true
        {1, 3, 4, 6},   // true
        {6, 6, 6, 6},   // true
        {0, 0, 0, 24},  // true
        {0, 0, 0, 1},   // false
        {2, 3, 4, 4},   // true
        {6, 6, 2, 2},   // true
        {1, 1, 1, 1}    // false
    };

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            vector<int>& nums = tests[i];
            bool res = sol.judgePoint24(nums);
            checksum += res ? static_cast<long long>(i + 1) : -static_cast<long long>(i + 1);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";
    return 0;
}