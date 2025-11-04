int main() {
    // Generate 10 diverse test inputs
    vector<int> t1; // empty
    vector<int> t2 = {42}; // single element
    vector<int> t3(20, 5); // all equal
    vector<int> t4; // strictly increasing
    for (int i = 1; i <= 100; ++i) t4.push_back(i);
    vector<int> t5; // strictly decreasing
    for (int i = 100; i >= 1; --i) t5.push_back(i);
    vector<int> t6 = {-5, 3, -2, 7, -1, 0, 4, -3, 2, -4, 8, -6, 6, -8, 5, -7}; // mixed small with negatives
    vector<int> t7 = {0,0,0,0,0,1,0,-1,-1,2,-2,3,-3,4,-4}; // zeros and duplicates
    vector<int> t8 = {INT_MAX, INT_MIN, INT_MAX - 1, INT_MIN + 1, 0, 1, -1, 2, -2, 3, -3}; // extremes and small values
    vector<int> t9; // alternating high/low causing many reverse pairs
    for (int i = 0; i < 100; ++i) t9.push_back((i % 2 == 0) ? 1000000000 : -1000000000);
    vector<int> t10; // pseudo-random large input (fixed seed)
    {
        uint32_t state = 123456789u;
        for (int i = 0; i < 512; ++i) {
            state = 1664525u * state + 1013904223u;
            int val = static_cast<int>(static_cast<int32_t>(state));
            t10.push_back(val);
        }
    }

    vector<vector<int>> prototypes = {t1, t2, t3, t4, t5, t6, t7, t8, t9, t10};

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (const auto& base : prototypes) {
            vector<int> work = base; // copy to preserve prototypes
            int result = sol.reversePairs(work);
            checksum += result;
            if (!work.empty()) {
                checksum += work[0]; // touch mutated data to avoid optimization
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}