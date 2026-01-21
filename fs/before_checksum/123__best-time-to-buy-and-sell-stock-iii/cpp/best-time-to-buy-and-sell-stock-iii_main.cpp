int main() {
    // Define 10 diverse test inputs
    vector<int> test1 = {};                                      // empty
    vector<int> test2 = {5};                                     // single element
    vector<int> test3 = {1, 2};                                  // simple increasing
    vector<int> test4 = {5, 1};                                  // simple decreasing
    vector<int> test5 = {1, 2, 3, 4, 5, 6};                      // strictly increasing
    vector<int> test6 = {6, 5, 4, 3, 2, 1};                      // strictly decreasing
    vector<int> test7 = {3, 3, 5, 0, 0, 3, 1, 4};                // typical multi-transaction pattern
    vector<int> test8 = {2, 1, 2, 0, 1};                         // small waves
    int m = numeric_limits<int>::max();
    vector<int> test9 = {m - 3, m - 2, m - 1, m, m - 4, m};      // near int max values

    // Long pseudo-random but deterministic pattern, non-negative prices
    vector<int> test10;
    test10.reserve(5000);
    for (int i = 0; i < 5000; ++i) {
        int price = (i * 97) % 1000;
        if (i % 7 == 0) price += 500;
        if (i % 13 == 0) price /= 2;
        test10.push_back(price);
    }

    vector<vector<int>> tests = {
        test1, test2, test3, test4, test5, test6, test7, test8, test9, test10
    };

    Solution sol;
    long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();

    const int iterations = 1;
    for (int iter = 0; iter < iterations; ++iter) {
        for (auto& t : tests) {
            checksum += sol.maxProfit(t);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;

    cout << "Checksum: " << checksum << "\n";
    cout << "Elapsed time (ms): " << ms.count() << "\n";

    return 0;
}