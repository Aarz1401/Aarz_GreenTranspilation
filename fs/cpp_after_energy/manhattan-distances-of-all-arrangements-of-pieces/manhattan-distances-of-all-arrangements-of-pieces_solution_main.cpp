int main() {
    // Define 10 diverse test inputs (m, n, k)
    vector<tuple<int,int,int>> tests = {
        {1, 1, 0},      // k < 2 -> 0
        {1, 1, 2},      // minimal grid with k=2
        {1, 5, 2},      // single row
        {2, 2, 2},      // small square
        {3, 4, 3},      // small rectangle
        {10, 10, 200},  // k too large -> 0
        {123, 456, 2},  // medium rectangle
        {100, 100, 5},  // moderate square
        {500, 200, 7},  // larger rectangle
        {1000, 1000, 2} // large square, triggers large precompute
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            int m, n, k;
            tie(m, n, k) = t;
            int res = sol.distanceSum(m, n, k);
            checksum += res;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ns): " << elapsed_ns << "\n";

    return 0;
}