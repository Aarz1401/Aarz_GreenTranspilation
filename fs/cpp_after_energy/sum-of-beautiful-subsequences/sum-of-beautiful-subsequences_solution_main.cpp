int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Generate 10 diverse test inputs
    vector<vector<int>> tests;
    tests.reserve(10);

    // 1) Small increasing sequence
    tests.push_back({1, 2, 3, 4, 5, 6});

    // 2) All equal numbers
    tests.push_back(vector<int>(20, 7));

    // 3) Primes
    tests.push_back({2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53});

    // 4) Powers of two
    tests.push_back({1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768});

    // 5) Multiples of 12
    {
        vector<int> v;
        for (int i = 1; i <= 15; ++i) v.push_back(12 * i);
        tests.push_back(move(v));
    }

    // 6) Descending sequence
    tests.push_back({50, 40, 30, 20, 10, 1});

    // 7) Mixed with near-maximum values
    tests.push_back({70000, 35000, 23333, 46666, 69999, 7000, 56000, 14000, 10000, 1});

    // 8) Single element
    tests.push_back({70000});

    // 9) Range 1..200
    {
        vector<int> v;
        v.reserve(200);
        for (int i = 1; i <= 200; ++i) v.push_back(i);
        tests.push_back(move(v));
    }

    // 10) Larger deterministic sequence of length 1000 within [1, 70000]
    {
        vector<int> v;
        v.reserve(1000);
        for (int i = 1; i <= 1000; ++i) {
            int x = (int)((i * 12345LL) % MAX_NUM) + 1;
            if (x > MAX_NUM) x = MAX_NUM; // safety, though not needed
            v.push_back(x);
        }
        tests.push_back(move(v));
    }

    Solution sol;
    long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& tc : tests) {
            checksum += sol.totalBeauty(tc);
            checksum %= 1000000007LL; // keep it bounded
        }
    }
    auto end = chrono::high_resolution_clock::now();
    double elapsed_ms = chrono::duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}