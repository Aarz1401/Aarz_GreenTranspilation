int main() {
    vector<TestCase> tests = {
        {0, 0, {}},
        {1, 0, {0}},
        {1, 1, {-1}},
        {2, 1, {2, -1}},
        {3, 2, {1, 1, 1}},
        {4, 0, {5, 5}},
        {5, 3, {0, 2, 5}},
        {6, 2, {1, 2, 3, 4}},
        {7, 4, {10, -20, 30}},
        {8, 5, {1, 0, 1, 0, 1}}
    };

    Solution sol;
    long long checksum = 0;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;

    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<int> nums = tc.nums; // copy to match function signature
            int res = sol.magicalSum(tc.m, tc.k, nums);
            checksum += res;
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<milliseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed << "\n";

    return 0;
}
