int main() {
    // Define 10 diverse test ranges
    vector<pair<long long, long long>> tests = {
        {0LL, 0LL},
        {1LL, 9LL},
        {10LL, 99LL},
        {100LL, 1000LL},
        {1LL, 1000000LL},
        {123456789LL, 987654321LL},
        {999999000000LL, 1000000000000LL},
        {555555555555555LL, 555555555555999LL},
        {1000000000000000LL, 1000000000010000LL},
        {314159265358979LL, 314159265359000LL}
    };

    Solution sol;
    unsigned long long checksum = 0;

    auto start = chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& t : tests) {
            long long res = sol.beautifulNumbers(t.first, t.second);
            checksum += static_cast<unsigned long long>(res) ^ static_cast<unsigned long long>(iter + 1);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    auto elapsed_us = chrono::duration_cast<chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}