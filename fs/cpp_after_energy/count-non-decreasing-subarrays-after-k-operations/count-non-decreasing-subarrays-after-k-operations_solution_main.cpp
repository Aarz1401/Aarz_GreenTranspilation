int main() {
    // Prepare 10 diverse test cases
    std::vector<TestCase> tests;
    tests.reserve(10);

    // 1) Empty array
    {
        TestCase t;
        t.nums = {};
        t.kLL = 0LL;
        t.useLL = true;
        tests.push_back(std::move(t));
    }

    // 2) Single element
    {
        TestCase t;
        t.nums = {5};
        t.kI = 0;
        t.useLL = false; // use int overload
        tests.push_back(std::move(t));
    }

    // 3) Strictly increasing
    {
        TestCase t;
        for (int i = 1; i <= 50; ++i) t.nums.push_back(i);
        t.kI = 5;
        t.useLL = false; // use int overload
        tests.push_back(std::move(t));
    }

    // 4) Strictly decreasing
    {
        TestCase t;
        for (int i = 50; i >= 1; --i) t.nums.push_back(i);
        t.kLL = 100000LL;
        t.useLL = true;
        tests.push_back(std::move(t));
    }

    // 5) All equal
    {
        TestCase t;
        t.nums.assign(100, 7);
        t.kI = 1234;
        t.useLL = false; // use int overload
        tests.push_back(std::move(t));
    }

    // 6) Alternating low/high
    {
        TestCase t;
        for (int i = 0; i < 100; ++i) {
            t.nums.push_back(1);
            t.nums.push_back(1000);
        }
        t.kLL = 5000LL;
        t.useLL = true;
        tests.push_back(std::move(t));
    }

    // 7) Mixed negatives and small positives (patterned)
    {
        TestCase t;
        for (int i = 0; i < 60; ++i) {
            t.nums.push_back((i % 10) - 5); // values in [-5,4]
        }
        t.kI = 50;
        t.useLL = false; // use int overload
        tests.push_back(std::move(t));
    }

    // 8) Near INT_MAX, small differences (avoid overflow)
    {
        TestCase t;
        int start = INT_MAX - 200;
        for (int i = 0; i <= 200; ++i) {
            t.nums.push_back(start + i);
        }
        t.kLL = 1000000LL;
        t.useLL = true;
        tests.push_back(std::move(t));
    }

    // 9) Pseudorandom values in [-10000, 10000], size 1000
    {
        TestCase t;
        std::mt19937 rng(42);
        std::uniform_int_distribution<int> dist(-10000, 10000);
        t.nums.resize(1000);
        for (int i = 0; i < 1000; ++i) t.nums[i] = dist(rng);
        t.kLL = 1000000000000LL; // large k
        t.useLL = true;
        tests.push_back(std::move(t));
    }

    // 10) Repeating segments: up, down, equal blocks
    {
        TestCase t;
        for (int rep = 0; rep < 5; ++rep) {
            for (int i = 1; i <= 20; ++i) t.nums.push_back(i);
            for (int i = 20; i >= 1; --i) t.nums.push_back(i);
            for (int i = 0; i < 10; ++i) t.nums.push_back(5);
        }
        t.kI = 10000;
        t.useLL = false; // use int overload
        tests.push_back(std::move(t));
    }

    Solution sol;
    volatile long long sink = 0; // to further discourage optimization
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            long long res = 0;
            if (tests[i].useLL) {
                res = sol.countNonDecreasingSubarrays(tests[i].nums, tests[i].kLL);
            } else {
                res = sol.countNonDecreasingSubarrays(tests[i].nums, tests[i].kI);
            }
            // Mix into checksum to avoid being optimized away
            checksum += (res ^ static_cast<long long>(iter + i * 97));
            sink = res; // use volatile sink
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (ns): " << elapsed_ns << "\n";
    return 0;
}