int main() {
    using namespace std;

    // Define 10 diverse test inputs (sorted positive integer arrays as per problem constraints)
    vector<vector<int>> nums_list = {
        {},                         // empty array
        {1},                        // single element
        {1, 3},                     // small gap
        {1, 2, 2},                  // covers without patches
        {1, 5, 10},                 // requires multiple patches
        {2, 3, 4},                  // missing initial 1
        {1, 2, 31, 33},             // large n stress
        {1, 4, 10, 25, 50},         // scattered coverage
        {1, 2, 3, 8, 9, 13},        // mixed small and medium
        {5, 10, 25}                 // missing several small numbers
    };

    vector<int> n_list = {
        7,                          // with empty array
        1,                          // minimal n
        6,                          // small n
        5,                          // small n, no patches
        20,                         // moderate n
        13,                         // moderate n, needs 1
        2147483647,                 // INT_MAX
        100,                        // moderate n
        20,                         // moderate n
        1000                        // large n with few nums
    };

    Solution sol;
    volatile long long checksum = 0;

    auto start = std::chrono::high_resolution_clock::now();
    const int iterations = 1000;
    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < nums_list.size(); ++i) {
            int res = sol.minPatches(nums_list[i], n_list[i]);
            checksum += (res ^ static_cast<int>(i) ^ iter);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();

    auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Checksum: " << checksum << "\n";
    std::cout << "Elapsed time (microseconds): " << elapsed_us << "\n";

    return 0;
}