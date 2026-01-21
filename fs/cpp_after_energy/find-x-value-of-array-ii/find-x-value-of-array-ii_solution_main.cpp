int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests = buildTests();
    Solution solver;

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    long long checksum = 0;

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& tc : tests) {
            vector<int> res = solver.resultArray(const_cast<vector<int>&>(tc.nums), const_cast<int&>(tc.k), const_cast<vector<vector<int>>&>(tc.queries));
            for (int v : res) checksum += v;
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Time (microseconds): " << elapsed_us << "\n";

    return 0;
}