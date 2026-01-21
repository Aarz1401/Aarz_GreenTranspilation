int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<TestCase> tests;
    tests.reserve(10);

    // 1) Empty array
    tests.push_back(TestCase{vector<int>{}, 0});

    // 2) Single prime element
    tests.push_back(TestCase{vector<int>{7}, 0});

    // 3) Single element equals 1
    tests.push_back(TestCase{vector<int>{1}, 0});

    // 4) All evens
    vector<int> t4(10, 4);
    tests.push_back(TestCase{t4, 2});

    // 5) All primes (odd), gcd of any segment > 1 unlikely
    tests.push_back(TestCase{vector<int>{5, 7, 11, 13, 17, 19, 23, 29, 31, 37}, 0});

    // 6) Mixed evens and odds
    tests.push_back(TestCase{vector<int>{2, 4, 6, 9, 3, 15, 10, 5, 25, 50, 75}, 1});

    // 7) Large array of ones
    vector<int> t7(500, 1);
    tests.push_back(TestCase{t7, 0});

    // 8) Patterned array with many multiples
    vector<int> t8;
    t8.reserve(300);
    int pattern8[] = {6, 10, 15, 21, 14, 22};
    for (int rep = 0; rep < 50; ++rep) {
        for (int v : pattern8) t8.push_back(v);
    }
    tests.push_back(TestCase{t8, 50});

    // 9) Array with zeros interspersed
    tests.push_back(TestCase{vector<int>{0, 0, 4, 0, 8, 0, 16, 0, 3, 0, 9, 0}, 3});

    // 10) Negatives and large numbers
    tests.push_back(TestCase{vector<int>{-4, -8, 12, -16, 24, -36, 48, -60, 2147483646, -2147483646, 1000000000, -1000000000}, 5});

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            int res = sol.minStable(tc.nums, tc.maxC);
            checksum += res;
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}