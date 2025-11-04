int main() {
    // Prepare 10 diverse test inputs
    vector<vector<int>> tests;
    // 1) Empty
    tests.push_back(vector<int>{});
    // 2) Single element
    tests.push_back(vector<int>{0});
    // 3) All zeros
    tests.push_back(vector<int>{0, 0, 0, 0, 0});
    // 4) Small mixed
    tests.push_back(vector<int>{1, 0});
    // 5) Example known case with non-zero best rotation
    tests.push_back(vector<int>{2, 3, 1, 4, 0});
    // 6) Another mixed case
    tests.push_back(vector<int>{1, 3, 0, 2, 4});
    // 7) Increasing sequence (best rotation likely 0)
    tests.push_back(vector<int>{0, 1, 2, 3, 4, 5, 6, 7});
    // 8) Deterministic pseudo-random for N=10
    {
        vector<int> t(10);
        for (int i = 0; i < 10; ++i) t[i] = (i * 3 + 1) % 10;
        tests.push_back(std::move(t));
    }
    // 9) All N-1 values
    tests.push_back(vector<int>{6, 6, 6, 6, 6, 6, 6});
    // 10) Larger N with deterministic pattern
    {
        int N = 1000;
        vector<int> t(N);
        for (int i = 0; i < N; ++i) t[i] = (i * i + 3 * i + 7) % N;
        tests.push_back(std::move(t));
    }

    Solution solver;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t j = 0; j < tests.size(); ++j) {
            int r = solver.bestRotation(tests[j]);
            checksum += (r ^ static_cast<int>(j) ^ iter);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time: " << elapsed_us << " microseconds\n";
    return 0;
}