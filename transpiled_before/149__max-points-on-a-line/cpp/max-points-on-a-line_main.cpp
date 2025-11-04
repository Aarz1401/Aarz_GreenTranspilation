int main() {
    using namespace std;
    using namespace std::chrono;

    Solution sol;
    auto tests = create_tests();

    long long checksum = 0;

    auto start = high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < tests.size(); ++i) {
            int result = sol.maxPoints(tests[i]);
            // Mix in iteration and index to the checksum
            checksum += static_cast<long long>(result) + static_cast<long long>(iter & 1) + static_cast<long long>(i);
        }
    }
    auto end = high_resolution_clock::now();

    auto elapsed_ns = duration_cast<nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}