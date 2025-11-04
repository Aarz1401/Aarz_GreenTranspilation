int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);
    tests.push_back({{3,4,6,5}, {9,1,2,5,8,3}, 5});
    tests.push_back({{6,7}, {6,0,4}, 5});
    tests.push_back({{}, {1,2,3,4,5}, 3});
    tests.push_back({{9,8,7}, {}, 2});
    tests.push_back({{1,1,1}, {1,1}, 0});
    tests.push_back({{5,9,1,3,7,2}, {3,9,5,2,1,8,6}, 13});
    tests.push_back({{2,5,6,4,4,0}, {7,3,8,0,6,5,7,6,2}, 15});
    tests.push_back({{0,1,2,3,4,5,6,7,8,9}, {9,8,7,6,5,4,3,2,1,0}, 10});
    tests.push_back({{0,0,0,0}, {0,0,0}, 6});
    tests.push_back({{9,9,9,1}, {9,9,8}, 5});

    Solution sol;
    uint64_t checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t tci = 0; tci < tests.size(); ++tci) {
            vector<int> a = tests[tci].nums1;
            vector<int> b = tests[tci].nums2;
            auto res = sol.maxNumber(a, b, tests[tci].k);
            checksum += res.size() + iter + tci;
            for (size_t r = 0; r < res.size(); ++r) {
                checksum ^= (uint64_t)(res[r] + 3) * (r + 11 + tci) + (uint64_t)(iter + 1);
                checksum += (checksum << 7) ^ (checksum >> 3); // mix
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed_ms = end - start;
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms.count() << "\n";
    return 0;
}