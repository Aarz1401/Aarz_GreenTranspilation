int main() {
    vector<TestCase> tests;

    // 1. Corners of a 10x10 square, moderate k
    tests.push_back(TestCase{
        10,
        {{0,0},{0,10},{10,10},{10,0}},
        2
    });

    // 2. Small side=1, all four corners/edges, higher k
    tests.push_back(TestCase{
        1,
        {{0,0},{0,1},{1,1},{1,0}},
        3
    });

    // 3. Mixed positions on all edges, side=50
    tests.push_back(TestCase{
        50,
        {{0,17},{12,50},{50,49},{33,0},{50,1},{0,25},{25,50},{50,25}},
        4
    });

    // 4. Single point, k=1
    tests.push_back(TestCase{
        5,
        {{0,3}},
        1
    });

    // 5. Many points on bottom edge, larger side and k
    tests.push_back(TestCase{
        100,
        {{0,0},{10,0},{20,0},{30,0},{40,0},{50,0},{60,0},{70,0},{80,0},{90,0},{100,0}},
        5
    });

    // 6. Duplicates and corners on side=7
    tests.push_back(TestCase{
        7,
        {{0,0},{0,0},{7,7},{7,7},{3,7},{7,3},{0,7}},
        3
    });

    // 7. Mixed across edges, side=12
    tests.push_back(TestCase{
        12,
        {{0,6},{4,12},{12,8},{8,0},{12,4},{0,0}},
        4
    });

    // 8. Large side, sparse points
    tests.push_back(TestCase{
        1000,
        {{0,0},{0,1000},{1000,1000},{1000,0},{500,1000},{1000,500}},
        2
    });

    // 9. Dense small square, many perimeter points
    tests.push_back(TestCase{
        2,
        {{0,0},{0,1},{0,2},{1,2},{2,2},{2,1},{2,0},{1,0}},
        4
    });

    // 10. Empty points with k=0 (early return path)
    tests.push_back(TestCase{
        3,
        {},
        0
    });

    Solution sol;
    long long checksum = 0;

    using clock_type = std::chrono::high_resolution_clock;
    auto start = clock_type::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int res = sol.maxDistance(tests[i].side, tests[i].points, tests[i].k);
            checksum += (res ^ static_cast<int>(i) ^ iter);
        }
    }

    auto end = clock_type::now();
    std::chrono::duration<double, std::milli> elapsed_ms = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms.count() << "\n";
    return 0;
}