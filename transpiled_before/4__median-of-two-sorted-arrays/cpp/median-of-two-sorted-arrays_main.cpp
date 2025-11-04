int main() {
    vector<pair<vector<int>, vector<int>>> tests;
    tests.reserve(10);

    tests.emplace_back(vector<int>{}, vector<int>{1});
    tests.emplace_back(vector<int>{}, vector<int>{1, 2, 3, 4});
    tests.emplace_back(vector<int>{1, 3}, vector<int>{2});
    tests.emplace_back(vector<int>{1, 2}, vector<int>{3, 4});
    tests.emplace_back(vector<int>{-5, -3, -1}, vector<int>{-2, 0, 2});
    tests.emplace_back(vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1});
    tests.emplace_back(vector<int>{INT_MIN, -1, 0, 1, INT_MAX}, vector<int>{-2, 2});
    {
        vector<int> evens;
        vector<int> odds;
        evens.reserve(100);
        odds.reserve(100);
        for (int i = 0; i < 100; ++i) {
            evens.push_back(i * 2);
            odds.push_back(i * 2 + 1);
        }
        tests.emplace_back(move(evens), move(odds));
    }
    tests.emplace_back(vector<int>{5}, vector<int>{1, 2, 3, 4, 6, 7, 8, 9, 10});
    tests.emplace_back(vector<int>{-10, -10, -5, 0, 0, 0, 5}, vector<int>{-7, -3, -3, 2, 4, 4, 20});

    Solution s;

    auto start = chrono::high_resolution_clock::now();
    double checksum = 0.0;
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            checksum += s.findMedianSortedArrays(tests[i].first, tests[i].second);
        }
    }
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, std::milli> elapsed = end - start;

    cout << fixed << setprecision(6);
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed.count() << "\n";
    return 0;
}