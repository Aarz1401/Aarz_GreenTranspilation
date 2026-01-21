int main() {
    // Prepare 10 diverse test inputs
    vector<vector<int>> tests;

    // 1) Empty
    tests.push_back({});

    // 2) Single element
    tests.push_back({1});

    // 3) All ones
    tests.push_back(vector<int>(8, 1));

    // 4) Primes
    tests.push_back({2, 3, 5, 7, 11, 13, 17, 19});

    // 5) Even numbers up to 20
    tests.push_back({2, 4, 6, 8, 10, 12, 14, 16, 18, 20});

    // 6) Mixed with repeats and multiples
    tests.push_back({6, 6, 3, 9, 12, 15, 30, 45, 60});

    // 7) Deterministic random in [1, 60], size 50
    {
        mt19937 rng(123456789u);
        uniform_int_distribution<int> dist(1, 60);
        vector<int> v;
        v.reserve(50);
        for (int i = 0; i < 50; ++i) v.push_back(dist(rng));
        tests.push_back(move(v));
    }

    // 8) Powers of two with duplicates
    tests.push_back({1, 2, 4, 8, 16, 32, 64, 64, 32, 16, 8, 4, 2, 1});

    // 9) Multiples of 6 up to 60, duplicated sequence
    tests.push_back({6, 12, 18, 24, 30, 36, 42, 48, 54, 60,
                     6, 12, 18, 24, 30, 36, 42, 48, 54, 60});

    // 10) Sequence 1..80
    {
        vector<int> v;
        v.reserve(80);
        for (int i = 1; i <= 80; ++i) v.push_back(i);
        tests.push_back(move(v));
    }

    Solution sol;
    long long checksum = 0;

    auto start = high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto &tc : tests) {
            checksum += sol.subsequencePairCount(tc);
        }
    }

    auto end = high_resolution_clock::now();
    auto elapsed_us = duration_cast<microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}