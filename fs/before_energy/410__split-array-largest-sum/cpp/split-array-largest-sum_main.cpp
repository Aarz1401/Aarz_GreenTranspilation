int main() {
    using namespace std;
    using namespace std::chrono;

    // Prepare 10 diverse test cases
    vector<vector<int>> arrays;
    vector<int> ms;

    // 1) Classic example
    arrays.push_back({7, 2, 5, 10, 8});
    ms.push_back(2);

    // 2) All ones, m equals size
    arrays.push_back({1, 1, 1, 1, 1});
    ms.push_back(5);

    // 3) Single large element
    arrays.push_back({1000000000});
    ms.push_back(1);

    // 4) Increasing sequence 1..1000, m = 10
    {
        vector<int> v(1000);
        iota(v.begin(), v.end(), 1);
        arrays.push_back(std::move(v));
        ms.push_back(10);
    }

    // 5) Large equal numbers, m = 5
    {
        vector<int> v(1000, 1000);
        arrays.push_back(std::move(v));
        ms.push_back(5);
    }

    // 6) All zeros
    arrays.push_back({0, 0, 0, 0});
    ms.push_back(2);

    // 7) Random moderate size, fixed seed for determinism
    {
        mt19937 rng(123456);
        uniform_int_distribution<int> dist(0, 10000);
        vector<int> v(200);
        for (int i = 0; i < (int)v.size(); ++i) v[i] = dist(rng);
        arrays.push_back(std::move(v));
        ms.push_back(20);
    }

    // 8) Alternating small and large values
    {
        vector<int> v;
        v.reserve(500);
        for (int i = 0; i < 500; ++i) v.push_back((i % 2 == 0) ? 1 : 1000000);
        arrays.push_back(std::move(v));
        ms.push_back(50);
    }

    // 9) m equals array size (result should be max element)
    {
        vector<int> v(50);
        for (int i = 0; i < 50; ++i) v[i] = (i * i) % 97 + 1;
        arrays.push_back(std::move(v));
        ms.push_back(50);
    }

    // 10) Descending values with step, m = 3
    {
        vector<int> v(100);
        for (int i = 0; i < 100; ++i) v[i] = 10000 - i * 50;
        arrays.push_back(std::move(v));
        ms.push_back(3);
    }

    Solution solver;
    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t t = 0; t < arrays.size(); ++t) {
            int res = solver.splitArray(arrays[t], ms[t]);
            // Mix in iter and index to prevent optimization
            checksum += static_cast<long long>(res) * (iter + 1) + static_cast<long long>(t);
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_ms = duration<double, std::milli>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";

    return 0;
}