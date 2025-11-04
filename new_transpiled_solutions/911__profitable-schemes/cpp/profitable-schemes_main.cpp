int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    tests.push_back(TestCase{1, 1, {1}, {1}});
    tests.push_back(TestCase{5, 3, {2, 2}, {2, 3}});
    tests.push_back(TestCase{10, 5, {2, 3, 5}, {6, 7, 8}});
    tests.push_back(TestCase{3, 0, {1, 1, 1}, {0, 0, 0}});
    tests.push_back(TestCase{0, 0, {}, {}});
    tests.push_back(TestCase{1, 2, {2}, {2}});
    tests.push_back(TestCase{5, 10, {2, 2, 1}, {5, 5, 1}});
    tests.push_back(TestCase{8, 7, {2, 3, 5, 1, 4}, {2, 2, 3, 1, 6}});
    tests.push_back(TestCase{50, 20, {5, 7, 10, 3, 6, 2, 8, 4, 9, 1}, {6, 7, 8, 3, 5, 1, 9, 2, 10, 0}});
    tests.push_back(TestCase{12, 15, {3, 5, 3, 3, 2, 6, 7}, {2, 10, 1, 1, 3, 8, 9}});

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            checksum += static_cast<uint64_t>(sol.profitableSchemes(t.n, t.minProfit, t.group, t.profit));
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << '\n';
    cout << "Elapsed time (ns): " << elapsed_ns << '\n';

    return 0;
}