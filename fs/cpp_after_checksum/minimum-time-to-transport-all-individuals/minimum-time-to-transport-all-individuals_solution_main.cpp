int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);
    tests.push_back(TestCase{1, 1, 1, {5}, {1.0}});
    tests.push_back(TestCase{2, 1, 2, {3, 7}, {0.8, 1.2}});
    tests.push_back(TestCase{3, 2, 3, {4, 2, 9}, {1.0, 1.5, 0.5}});
    tests.push_back(TestCase{4, 2, 4, {2, 5, 1, 7}, {0.9, 1.1, 1.3, 0.7}});
    tests.push_back(TestCase{5, 3, 3, {8, 3, 6, 2, 9}, {1.0, 0.95, 1.2}});
    tests.push_back(TestCase{6, 2, 5, {5, 4, 7, 3, 8, 6}, {1.2, 0.8, 1.0, 1.5, 0.6}});
    tests.push_back(TestCase{7, 3, 2, {9, 1, 4, 7, 2, 5, 3}, {1.1, 0.9}});
    tests.push_back(TestCase{8, 4, 4, {6, 2, 9, 1, 7, 3, 8, 5}, {1.0, 0.75, 1.25, 0.5}});
    tests.push_back(TestCase{9, 3, 6, {3, 6, 1, 8, 2, 7, 4, 9, 5}, {0.9, 1.05, 1.2, 0.8, 1.3, 0.7}});
    tests.push_back(TestCase{5, 1, 7, {10, 3, 8, 2, 6}, {0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1}});

    Solution sol;
    double checksum = 0.0;

    using chrono::high_resolution_clock;
    using chrono::duration;
    using chrono::duration_cast;

    auto start = high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.minTime(tc.n, tc.k, tc.m, tc.time, tc.mul);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed = duration_cast<chrono::duration<double, std::milli>>(end - start).count();

    cout << fixed << setprecision(6);
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed << "\n";

    return 0;
}