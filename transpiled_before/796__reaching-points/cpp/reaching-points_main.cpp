int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 10 diverse test inputs (sx, sy, tx, ty)
    volatile int sx_cases[10] = {1, 1, 5, 2, 7, 4, 5, 1, 5, 4};
    volatile int sy_cases[10] = {1, 1, 8, 3, 13, 10, 7, 2, 11, 1};
    volatile int tx_cases[10] = {3, 2, 5, 5, 1000000008, 1000000009, 20, 999999937, 1000000002, 1000000000};
    volatile int ty_cases[10] = {5, 2, 8, 8, 13, 1000000015, 6, 2, 11, 1};

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (int i = 0; i < 10; ++i) {
            int sx = sx_cases[i];
            int sy = sy_cases[i];
            int tx = tx_cases[i];
            int ty = ty_cases[i];
            bool res = sol.reachingPoints(sx, sy, tx, ty);
            checksum += res ? (i + 1) : 0;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << elapsed_ms << "\n";
    return 0;
}